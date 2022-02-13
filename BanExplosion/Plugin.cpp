#include "pch.h"
#include <Global.h>
#include <LLAPI.h>
#include <MC/Player.hpp>
#include <MC/Level.hpp>
#include <EventAPI.h>
#include <MC/Block.hpp>
#include <RegCommandAPI.h>
#include <string>
#include "SimpleIni.h"

using namespace RegisterCommandHelper;
using namespace std;

#define _CONF_PATH "plugins/BanExplosion/config.ini"

CSimpleIniA ini;

Logger logger("BanExplosion");
LL::Version ver(1, 5, 7);

// 防爆
bool suspend = false;

bool ReloadIni()
{
    ini.Reset();
    return ini.LoadFile(_CONF_PATH) == 0;
}

class BanExplodeCommand : public Command {
    enum class EXPOP :int {
        off,
        on,
        reload,
    } op;

    virtual void execute(CommandOrigin const& ori, CommandOutput& outp) const
    {
        switch (op)
        {
        case EXPOP::off:
            suspend = true;
            logger.info("=== 自定义防爆规则已临时关闭 ===");
            break;
        case EXPOP::on:
            suspend = false;
            logger.info("=== 自定义防爆规则已启用 ===");
            break;
        case EXPOP::reload:
            if (ReloadIni())
                logger.info("配置文件已重新加载。");
            else
                logger.error("配置文件解析失败！插件将不会正常工作");
            break;
        default:
            logger.warn("未知操作！");
        }
    }
public:
    static void setup(CommandRegistry* registry) {
        registry->registerCommand(
            "banexp", "Control custom explosion rule", CommandPermissionLevel::GameMasters, { (CommandFlagValue)0 },
            { (CommandFlagValue)0x80 });
        registry->addEnum<EXPOP>("Operation",
            {
                    {"off", EXPOP::off},
                    {"on", EXPOP::on},
                    {"reload", EXPOP::reload},
            });
        registry->registerOverload<BanExplodeCommand>(
            "banexp",
            makeMandatory<CommandParameterDataType::ENUM>(&BanExplodeCommand::op, "operation", "Operation"));
    }
};

// Main

void entry()
{
    LL::registerPlugin("BanExplosion", "Customize your explosion destroy rule!", ver, {
        {"GitHub","https://github.com/yqs112358/LLPlugins"} });

    ini.SetUnicode(true);
    auto res = ini.LoadFile(_CONF_PATH);
    if (res < 0)
    {
        logger.error("防爆插件加载配置文件失败！");
        logger.error("插件将不会正常工作。");
        return;
    }

    Event::PlayerUseRespawnAnchorEvent::subscribe([](const Event::PlayerUseRespawnAnchorEvent &ev) {
        if (!suspend && ini.GetBoolValue("minecraft:respawn_anchor", "NoExplosion"))
            return false;
        return true;
    });

    Event::WitherBossDestroyEvent::subscribe([](const Event::WitherBossDestroyEvent &ev) {
        if (!suspend && ini.GetBoolValue("minecraft:wither", "NoDestroyBlock"))
            return false;
        return true;
    });

    Event::EntityExplodeEvent::subscribe_ref([](Event::EntityExplodeEvent& ev) {
        if (suspend)
            return true;
        string name = ev.mActor->getTypeName();
        if (ini.GetBoolValue(name.c_str(), "NoExplosion"))
            return false;
        if (ini.GetBoolValue(name.c_str(), "NoDestroyBlock"))
            ev.mBreaking = false;
        return true;
    });

    Event::BlockExplodeEvent::subscribe_ref([](Event::BlockExplodeEvent& ev) {
        if (suspend)
            return true;
        string name = ev.mBlockInstance.getBlock()->getTypeName();

        /*if (ini.GetBoolValue(name.c_str(), "NoExplosion"))
            return false;
        if (ini.GetBoolValue(name.c_str(), "NoDestroyBlock"))
            ev.mBreaking = false;*/

        if (ini.GetBoolValue("minecraft:bed", "NoExplosion"))           //bed
            return false;
        if (ini.GetBoolValue("minecraft:bed", "NoDestroyBlock"))
            ev.mBreaking = false;
        return true;
    });

    Event::PlayerUseRespawnAnchorEvent::subscribe([](const Event::PlayerUseRespawnAnchorEvent& ev) {
        if (suspend)
            return true;
        if (ini.GetBoolValue("minecraft:respawn_anchor", "NoExplosion"))
            return false;
        else
            return true;
    });

    Event::RegCmdEvent::subscribe([](Event::RegCmdEvent ev)
    {
            BanExplodeCommand::setup(ev.mCommandRegistry);
            return true;
    });

    logger.info("BanExplosion自定义防爆插件-已装载  当前版本：{}", ver.toString());
    logger.info("配置文件位于：{}", _CONF_PATH);
    logger.info("作者：yqs112358   首发平台：MineBBS");
    logger.info("欲联系作者可前往MineBBS论坛");
}