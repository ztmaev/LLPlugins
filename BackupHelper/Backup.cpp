#include "pch.h"
#include "ConfigFile.h"
#include "Backup.h"
#include "Tools.h"
#include <string>
#include <thread>
#include <filesystem>
using namespace std;

#define TEMP_DIR ".\\plugins\\BackupHelper\\temp\\"
#define ZIP_PATH ".\\plugins\\BackupHelper\\7za.exe"

bool isWorking = false;
bool isCopying = false;
Player* nowPlayer = nullptr;

struct SnapshotFilenameAndLength
{
	string path;
	size_t size;
};

void SuccessEnd()
{
    SendFeedback(nowPlayer, "备份成功结束");
    nowPlayer = nullptr;
    isWorking = false;
}

void FailEnd(int code=-1)
{
    SendFeedback(nowPlayer, string("备份失败！") + (code == -1 ? "" : "错误码：" + to_string(code)));
    nowPlayer = nullptr;
    isWorking = false;
}

void ControlResourceUsage(HANDLE process)
{
    //Job
    HANDLE hJob = CreateJobObject(NULL, L"BACKUP_HELPER_HELP_PROGRAM");
    if (hJob > 0)
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
    wstring dirFind = U8StringToWString(ini.GetValue("Main", "BackupPath", "backup")) + L"\\*";

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
                DeleteFile((dirFind + findFileData.cFileName).c_str());
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
    filesystem::create_directories(TEMP_DIR);
    filesystem::copy(".\\worlds\\" + worldName, TEMP_DIR + worldName, std::filesystem::copy_options::recursive);

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
    //Get Name
    char timeStr[32];
    time_t nowtime;
    time(&nowtime);
    struct tm* info = localtime(&nowtime);
    strftime(timeStr, sizeof(timeStr), "%Y-%m-%d_%H-%M-%S", info);

    string backupPath = ini.GetValue("Main", "BackupPath", "backup");
    int level = ini.GetLongValue("Main", "Compress", 0);

    char tmpCmdStr[_MAX_PATH * 4] = { 0 };
    sprintf(tmpCmdStr, "%s a \"%s\\%s_%s.7z\" \"%s%s\" -sdel -mx%d -mmt"
        , ZIP_PATH, backupPath.c_str(), worldName.c_str(), timeStr, TEMP_DIR, worldName.c_str(), level);

    wchar_t cmdStr[_MAX_PATH * 4] = { 0 };
    U8StringToWString(tmpCmdStr).copy(cmdStr, strlen(tmpCmdStr), 0);

    //Prepare for output
    STARTUPINFO si = { sizeof(STARTUPINFO) };
    SECURITY_ATTRIBUTES sa = { sizeof(SECURITY_ATTRIBUTES),NULL,TRUE };
    HANDLE hZipOutput = INVALID_HANDLE_VALUE;

    string zipLog = ini.GetValue("Main", "7zLog", "");
    if (!zipLog.empty())
    {
        hZipOutput = CreateFile(U8StringToWString(zipLog).c_str(), GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE,
            &sa, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hZipOutput != INVALID_HANDLE_VALUE)
        {
            si.hStdOutput = hZipOutput;
            si.hStdError = hZipOutput;
        }
        else
            si.hStdOutput = si.hStdError = INVALID_HANDLE_VALUE;
    }
    else
        si.hStdOutput = si.hStdError = INVALID_HANDLE_VALUE;

    si.dwFlags = STARTF_USESTDHANDLES;

    //Create zip process
    PROCESS_INFORMATION pi;
    ZeroMemory(&pi, sizeof(pi));

    if (!CreateProcessW(NULL, cmdStr, NULL, NULL, TRUE, CREATE_SUSPENDED, NULL, NULL, &si, &pi))
    {
        SendFeedback(nowPlayer, "Failed to start zip process!");
        FailEnd(GetLastError());
    }

    ControlResourceUsage(pi.hProcess);
    ResumeThread(pi.hThread);

    DWORD res;
    if ((res = WaitForSingleObject(pi.hProcess, ini.GetLongValue("Main", "MaxWaitForZip", -1))) == WAIT_TIMEOUT || res == WAIT_FAILED)
    {
        SendFeedback(nowPlayer, "Zip process timeout!");
        FailEnd(GetLastError());
    }
    if (hZipOutput != INVALID_HANDLE_VALUE)
        CloseHandle(hZipOutput);
    CloseHandle(pi.hProcess);
}

void StartBackup()
{
    isWorking = true;
    ClearOldBackup();
    try
    {
        liteloader::runcmd("save hold");
    }
    catch(const seh_exception &e)
    {
        SendFeedback(nowPlayer, "Failed to start backup snapshot!");
        FailEnd(e.code());
    }
}

#define RETRY_TIME 60
int resumeTime = -1;

THook(void, "?tick@ServerLevel@@UEAAXXZ",
    void* _this)
{
    if (resumeTime > 0)
        --resumeTime;
    else if (resumeTime == 0)
    {
        if (!isWorking)
            resumeTime = -1;
        try
        {
            auto res = liteloader::runcmdEx("save resume");
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
        }
    }

    try
    {
        return original(_this);
    }
    catch (const seh_exception& e)
    {
        SendFeedback(nowPlayer, "Crash in resume! Error Code:" + to_string(e.code()));
        if (isWorking)
            resumeTime = RETRY_TIME;
    }
}

struct DBStorage;
THook(vector<SnapshotFilenameAndLength>&, "?createSnapshot@DBStorage@@UEAA?AV?$vector@USnapshotFilenameAndLength@@V?$allocator@USnapshotFilenameAndLength@@@std@@@std@@AEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@3@@Z",
    DBStorage* _this, vector<SnapshotFilenameAndLength>& fileData, string& worldName)
{
    isWorking = true;
    dbs = _this;
	auto& files = original(_this, fileData, worldName);
    CopyFiles(worldName, files);

    thread([worldName]()
    {
        ZipFiles(worldName);
        CleanTempDir();
        SuccessEnd();
    }).detach();

    resumeTime = 20;
    return files;
}