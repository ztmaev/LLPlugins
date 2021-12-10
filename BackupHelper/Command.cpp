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

using namespace RegisterCommandHelper;

class BackupCommand : public Command {
    enum BackupOP :int {
        reload = 1,
        cancel = 2,
    } op;
    bool op_isSet = false;

    virtual void execute(CommandOrigin const& ori, CommandOutput& outp) const
    {
        Player* player = (Player*)ori.getEntity();
        if (!op_isSet) {
            CmdBackup(player);
        }
        switch (op)
        {
        case reload:
            CmdReloadConfig(player);
            break;
        case cancel:
            CmdCancel(player);
            break;
        default:
            Logger::Warn("未知操作！");
        }
    }
public:
    static void setup(CommandRegistry* registry) {
        registry->registerCommand(
            "backup", "Create a backup", CommandPermissionLevel::GameMasters, { (CommandFlagValue)0 },
            { (CommandFlagValue)0x80 });
        registry->addEnum<BackupOP>("operation",
            {
                    {"cancel", cancel},
                    {"reload", reload},
            });
        registry->registerOverload<BackupCommand>(
            "plugins",
            makeOptional<CommandParameterDataType::ENUM>(&BackupCommand::op, "operation", "operation", &BackupCommand::op_isSet));
    }
};

void registryCommand(CommandRegistry* registry) {
    BackupCommand::setup(registry);
}