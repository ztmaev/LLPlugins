#include "pch.h"
#include <filesystem>
#include "ConfigFile.h"
#include "Backup.h"
#include "Tools.h"
#include "i18n.h"
using namespace std;

#define _VER "2.0.0"
CSimpleIniA ini;


bool RegisterCmd(const string& cmd, const string& describe, int cmdLevel)
{
    SymCall("?registerCommand@CommandRegistry@@QEAAXAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PEBDW4CommandPermissionLevel@@UCommandFlag@@3@Z",
        void, void*, const string&, const char*, char, char, char)
        (CmdRegGlobal, cmd, describe.c_str(), cmdLevel, 0, 0x40);
    return true;
}

// ===== onConsoleCmd =====
THook(bool, "??$inner_enqueue@$0A@AEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@?$SPSCQueue@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@$0CAA@@@AEAA_NAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z",
    void* _this, string& cmd)
{
    if (cmd.front() == '/')
        cmd = cmd.substr(1);
    if (cmd == "stop" && isCopying)
    {
        ErrorOutput("Cannot stop! Backuping is working now.");
        return false;
    }
    return original(_this, cmd);
}

bool Raw_IniOpen(const string& path, const std::string& defContent)
{
    if (!filesystem::exists(path))
    {
        //创建新的
        filesystem::create_directories(filesystem::path(path).remove_filename().u8string());

        ofstream iniFile(path);
        if (iniFile.is_open() && defContent != "")
            iniFile << defContent;
        iniFile.close();
    }

    //已存在
    ini.SetUnicode(true);
    auto res = ini.LoadFile(path.c_str());
    if (res < 0)
    {
        ErrorOutput("Failed to open Config File!");
        return false;
    }
    else
    {
        return true;
    }
}

void entry()
{
    _set_se_translator(seh_exception::TranslateSEHtoCE);

    Raw_IniOpen(_CONFIG_FILE,"");
    InitI18n(string("plugins/BackupHelper/LangPack/") + ini.GetValue("Main", "Language", "en_US") + ".json");

    cout << "[BackupHelper] BackupHelper存档备份助手-已装载  当前版本："  << _VER << endl;
    cout << "[BackupHelper] OP/后台命令： backup 开始备份" << endl;
    cout << "[BackupHelper] OP/后台命令： backup reload 重新加载配置文件" << endl;
    cout << "[BackupHelper] 作者：yqs112358   首发平台：MineBBS" << endl;
    cout << "[BackupHelper] 欲联系作者可前往MineBBS论坛" << endl;

    //Cleanup Old
    if (filesystem::exists("plugins/BackupHelper.lxl.js"))
        filesystem::remove("plugins/BackupHelper.lxl.js");
    if (filesystem::exists("plugins/BackupHelper/BackupRunner.exe"))
        filesystem::remove("plugins/BackupHelper/BackupRunner.exe");

    Event::addEventListener([](RegCmdEV e) {
        CMDREG::SetCommandRegistry(e.CMDRg);
        RegisterCmd("backup", "Create a backup", 4);
        RegisterCmd("backup", "Create a backup", 1);
    });
}