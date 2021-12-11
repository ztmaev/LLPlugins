#include "pch.h"
#include "BackupCommand.h"
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

#ifdef LEGACY_COMMAND

#include "../Header/MC/CommandContext.hpp"
#include "../Header/MC/CommandOrigin.hpp"
THook(bool, "?executeCommand@MinecraftCommands@@QEBA?AUMCRESULT@@V?$shared_ptr@VCommandContext@@@std@@_N@Z",
    MinecraftCommands* _this, unsigned int* a2, std::shared_ptr<CommandContext> x, char a4)
{
    Player* player = (Player *)x->getOrigin().getPlayer();
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

#else

using namespace RegisterCommandHelper;

void BackupCommand::execute(CommandOrigin const& ori, CommandOutput& outp) const
{
    Player* player = (Player*)ori.getPlayer();
    if (!op_isSet) {
        CmdBackup(player);
        return;
    }
    switch (op)
    {
    case BackupOP::reload:
        CmdReloadConfig(player);
        break;
    case BackupOP::cancel:
        CmdCancel(player);
        break;
    default:
        Logger::Warn("未知操作！");
    }
}

void BackupCommand::setup(CommandRegistry* registry) {
    registry->registerCommand(
        "backup", "Create a backup", CommandPermissionLevel::GameMasters, { (CommandFlagValue)0 },
        { (CommandFlagValue)0x80 });
    registry->addEnum<BackupOP>("operation",
        {
                {"cancel", BackupOP::cancel},
                {"reload", BackupOP::reload},
        });
    registry->registerOverload<BackupCommand>(
        "backup",
        makeOptional<CommandParameterDataType::ENUM>(&BackupCommand::op, "operation", "operation", &BackupCommand::op_isSet));
}
#endif //LEGACY_COMMAND