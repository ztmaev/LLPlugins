#include "pch.h"
#include "Backup.h"
#include "ConfigFile.h"
#include "Tools.h"
using namespace std;

void CmdReloadConfig(Player *p)
{
    ini.Reset();
    auto res = ini.LoadFile(_CONFIG_FILE);
    if (res < 0)
    {
        SendFeedback(p, "Failed to open Config File!");
    }
    else
    {
        SendFeedback(p, "Config File reloaded.");
    }
}

void CmdBackup(Player* p)
{
    Player* oldp = nowPlayer;
    nowPlayer = p;
    if (isWorking)
    {
        SendFeedback(p, "An existing backup is working now...");
        nowPlayer = oldp;
    }
    else
        StartBackup();
}

void CmdCancel(Player* p)
{
    if (isWorking)
    {
        isWorking = false;
        nowPlayer = nullptr;
        SendFeedback(p, "Backup Canceled.");
    }
    else
    {
        SendFeedback(p, "No backup is working now.");
    }
}


THook(bool, "?executeCommand@MinecraftCommands@@QEBA?AUMCRESULT@@V?$shared_ptr@VCommandContext@@@std@@_N@Z",
    MinecraftCommands* _this, unsigned int* a2, std::shared_ptr<CommandContext> x, char a4)
{
    Player* player = MakeSP(x->getOrigin());

    string cmd = x->getCmd();
    if (cmd.front() == '/')
        cmd = cmd.substr(1);
    if (cmd.empty())
        return original(_this, a2, x, a4);

    if (cmd == "backup reload")
    {
        CmdReloadConfig(player);
        return false;
    }
    else if (cmd == "backup")
    {
        CmdBackup(player);
        return false;
    }
    else if (cmd == "backup cancel")
    {
        CmdCancel(player);
        return false;
    }
    return original(_this, a2, x, a4);
}