#include "pch.h"
#include "ConfigFile.h"
#include "Backup.h"
#include "Tools.h"
#include <shellapi.h>
#include <string>
#include <thread>
#include <filesystem>
using namespace std;

#define TEMP_DIR ".\\plugins\\BackupHelper\\temp\\"
#define ZIP_PATH ".\\plugins\\BackupHelper\\7za.exe"

bool isWorking = false;
Player* nowPlayer = nullptr;

struct SnapshotFilenameAndLength
{
	string path;
	size_t size;
};

void ResumeBackup();

void SuccessEnd()
{
    SendFeedback(nowPlayer, "备份成功结束");
    nowPlayer = nullptr;
    isWorking = false;
}

void FailEnd(int code=-1)
{
    SendFeedback(nowPlayer, string("备份失败！") + (code == -1 ? "" : "错误码：" + to_string(code)));
    ResumeBackup();
    nowPlayer = nullptr;
    isWorking = false;
}

void ControlResourceUsage(HANDLE process)
{
    //Job
    HANDLE hJob = CreateJobObject(NULL, L"BACKUP_HELPER_HELP_PROGRAM");
    if (hJob)
    {
        JOBOBJECT_BASIC_LIMIT_INFORMATION limit = { 0 };
        limit.PriorityClass = BELOW_NORMAL_PRIORITY_CLASS;
        limit.LimitFlags = JOB_OBJECT_LIMIT_PRIORITY_CLASS;

        SetInformationJobObject(hJob, JobObjectBasicLimitInformation, &limit, sizeof(limit));
        AssignProcessToJobObject(hJob, process);
    }

    //CPU Limit
    SYSTEM_INFO si;
    memset(&si, 0, sizeof(SYSTEM_INFO));
    GetSystemInfo(&si);
    DWORD cpuCnt = si.dwNumberOfProcessors;
    DWORD cpuMask = 1;
    if (cpuCnt > 1)
    {
        if (cpuCnt % 2 == 1)
            cpuCnt -= 1;
        cpuMask = int(sqrt(1 << cpuCnt)) - 1;    //sqrt(2^n)-1
    }
    SetProcessAffinityMask(process, cpuMask);
}

void ClearOldBackup()
{
    int days = ini.GetLongValue("Main", "MaxStorageTime", -1);
    if (days < 0)
        return;
    SendFeedback(nowPlayer, "备份最长保存时间：" + to_string(days) + "天");

    time_t timeStamp = time(NULL) - days * 86400;
    wstring dirBackup = U8StringToWString(ini.GetValue("Main", "BackupPath", "backup"));
    wstring dirFind = dirBackup + L"\\*";

    WIN32_FIND_DATA findFileData;
    ULARGE_INTEGER createTime;
    int clearCount = 0;

    HANDLE hFind = FindFirstFile(dirFind.c_str(), &findFileData);
    if (hFind == INVALID_HANDLE_VALUE)
    {
        SendFeedback(nowPlayer, "Fail to locate old backups.");
        return;
    }
    do
    {
        if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            continue;
        else
        {
            createTime.LowPart = findFileData.ftCreationTime.dwLowDateTime;
            createTime.HighPart = findFileData.ftCreationTime.dwHighDateTime;
            if (createTime.QuadPart / 10000000 - 11644473600 < (ULONGLONG)timeStamp)
            {
                DeleteFile((dirBackup + L"\\" + findFileData.cFileName).c_str());
                ++clearCount;
            }
        }
    } while (FindNextFile(hFind, &findFileData));
    FindClose(hFind);

    if (clearCount > 0)
        SendFeedback(nowPlayer, to_string(clearCount) + " old backups cleaned.");
    return;
}

void CleanTempDir()
{
    error_code code;
    filesystem::remove_all(filesystem::path(TEMP_DIR),code);
}

void CopyFiles(const string &worldName, vector<SnapshotFilenameAndLength>& files)
{
    SendFeedback(nowPlayer, "已抓取到BDS待备份文件清单。正在处理...");
    SendFeedback(nowPlayer, "正在复制文件...");

    //Copy Files
    CleanTempDir();
    error_code ec;
    filesystem::create_directories(TEMP_DIR,ec);
    ec.clear();
    
    filesystem::copy(".\\worlds\\" + worldName, TEMP_DIR + worldName, std::filesystem::copy_options::recursive,ec);
    if (ec.value() != 0)
    {
        SendFeedback(nowPlayer, "Failed to copy save files!\n" + ec.message());
        FailEnd(GetLastError());
    }

    //Truncate
    for (auto& file : files)
    {
        string toFile = TEMP_DIR + file.path;

        LARGE_INTEGER pos;
        pos.QuadPart = file.size;
        LARGE_INTEGER curPos;
        HANDLE hSaveFile = CreateFileW(U8StringToWString(toFile).c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, 0);

        if (hSaveFile == INVALID_HANDLE_VALUE || !SetFilePointerEx(hSaveFile, pos, &curPos, FILE_BEGIN)
            || !SetEndOfFile(hSaveFile))
        {
            SendFeedback(nowPlayer, "Failed to truncate " + toFile + "!");
            FailEnd(GetLastError());
        }
        CloseHandle(hSaveFile);
    }
    SendFeedback(nowPlayer, "压缩过程可能花费相当长的时间，请耐心等待");
}

void ZipFiles(const string &worldName)
{
    try
    {
        //Get Name
        char timeStr[32];
        time_t nowtime;
        time(&nowtime);
        struct tm* info = localtime(&nowtime);
        strftime(timeStr, sizeof(timeStr), "%Y-%m-%d_%H-%M-%S", info);

        string backupPath = ini.GetValue("Main", "BackupPath", "backup");
        int level = ini.GetLongValue("Main", "Compress", 0);

        //Prepare command line
        char tmpParas[_MAX_PATH * 4] = { 0 };
        sprintf(tmpParas, "a \"%s\\%s_%s.7z\" \"%s%s\" -sdel -mx%d -mmt"
            , backupPath.c_str(), worldName.c_str(), timeStr, TEMP_DIR, worldName.c_str(), level);

        wchar_t paras[_MAX_PATH * 4] = { 0 };
        U8StringToWString(tmpParas).copy(paras, strlen(tmpParas), 0);

        DWORD maxWait = ini.GetLongValue("Main", "MaxWaitForZip", 0);
        if (maxWait <= 0)
            maxWait = 0xFFFFFFFF;
        else
            maxWait *= 1000;

        //Start Process
        wstring zipPath = U8StringToWString(ZIP_PATH);
        SHELLEXECUTEINFO sh = { sizeof(SHELLEXECUTEINFO) };
        sh.fMask = SEE_MASK_NOCLOSEPROCESS;
        sh.hwnd = NULL;
        sh.lpVerb = L"open";
        sh.nShow = SW_HIDE;
        sh.lpFile = zipPath.c_str();
        sh.lpParameters = paras;
        if (!ShellExecuteEx(&sh))
        {
            SendFeedback(nowPlayer, "Fail to create Zip process!");
            FailEnd(GetLastError());
        }
        
        ControlResourceUsage(sh.hProcess);
        SetPriorityClass(sh.hProcess, BELOW_NORMAL_PRIORITY_CLASS);

        //Wait
        DWORD res;
        if ((res = WaitForSingleObject(sh.hProcess, maxWait)) == WAIT_TIMEOUT || res == WAIT_FAILED)
        {
            SendFeedback(nowPlayer, "Zip process timeout!");
            FailEnd(GetLastError());
        }
        CloseHandle(sh.hProcess);
    }
    catch (const seh_exception& e)
    {
        SendFeedback(nowPlayer, "Exception in zip process! Error Code:" + to_string(e.code()));
        FailEnd(GetLastError());
    }
    catch (const exception& e)
    {
        SendFeedback(nowPlayer, string("Exception in zip process!\n") + e.what());
        FailEnd(GetLastError());
    }
}

void StartBackup()
{
    SendFeedback(nowPlayer, "备份已启动");
    isWorking = true;
    ClearOldBackup();
    try
    {
        Level::runcmd("save hold");
    }
    catch(const seh_exception &e)
    {
        SendFeedback(nowPlayer, "Failed to start backup snapshot!");
        FailEnd(e.code());
    }
}

#define RETRY_TIME 60
int resumeTime = -1;

void ResumeBackup()
{
    try
    {
        std::pair<bool, string> res = Level::runcmdEx("save resume");
        if (!res.first)
        {
            SendFeedback(nowPlayer, "Failed to resume backup snapshot!");
            if (isWorking)
                resumeTime = RETRY_TIME;
            else
                resumeTime = -1;
        }
        else
        {
            SendFeedback(nowPlayer, res.second);
            resumeTime = -1;
        }
    }
    catch (const seh_exception& e)
    {
        SendFeedback(nowPlayer, "Failed to resume backup snapshot! Error Code:" + to_string(e.code()));
        if (isWorking)
            resumeTime = RETRY_TIME;
        else
            resumeTime = -1;
    }
}

THook(void, "?tick@ServerLevel@@UEAAXXZ",
    void* _this)
{
    if (resumeTime > 0)
        --resumeTime;
    else if (resumeTime == 0)
    {
        if (!isWorking)
            resumeTime = -1;
        ResumeBackup();
    }
    return original(_this);
}

struct DBStorage;
THook(vector<SnapshotFilenameAndLength>&, "?createSnapshot@DBStorage@@UEAA?AV?$vector@USnapshotFilenameAndLength@@V?$allocator@USnapshotFilenameAndLength@@@std@@@std@@AEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@3@@Z",
    DBStorage* _this, vector<SnapshotFilenameAndLength>& fileData, string& worldName)
{
    isWorking = true;
	auto& files = original(_this, fileData, worldName);
    CopyFiles(worldName, files);

    thread([worldName]()
    {
        _set_se_translator(seh_exception::TranslateSEHtoCE);
        ZipFiles(worldName);
        CleanTempDir();
        SuccessEnd();
    }).detach();

    resumeTime = 20;
    return files;
}