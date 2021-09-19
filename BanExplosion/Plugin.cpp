#include "pch.h"
#include "headers/lbpch.h"
#include "headers/mc/OffsetHelper.h"
#include "headers/api/commands.h"
#include "headers/loader/Loader.h"
#include <string>
#include "SimpleIni.h"
using namespace std;

#define _VER "1.5.2"
#define _CONF_PATH "plugins/BanExplosion/config.ini"

CSimpleIniA ini;

//Utils
std::string Raw_GetEntityTypeName(Actor* actor)
{
    return SymCall("?EntityTypeToString@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@W4ActorType@@W4ActorTypeNamespaceRules@@@Z",
        string, int, int)
        (actor->getEntityTypeId(), 1);
}

// 防爆
bool suspend = false;

// ===== onExplode & onBedExplode =====
THook(bool, "?explode@Level@@UEAAXAEAVBlockSource@@PEAVActor@@AEBVVec3@@M_N3M3@Z",
    Level* _this, BlockSource* bs, Actor* actor, Vec3* pos, float power, bool isFire, bool isDestroy, float range, bool a9)
{
    if (!suspend)
    {
        if (actor)
        {
            //常规
            string name = Raw_GetEntityTypeName(actor);
            if (ini.GetBoolValue(name.c_str(), "NoExplosion"))
                return false;
            if (ini.GetBoolValue(name.c_str(), "NoDestroyBlock"))
                isDestroy = false;
        }
        else
        {
            //床
            if (ini.GetBoolValue("minecraft:bed", "NoExplosion"))
                return false;
            if (ini.GetBoolValue("minecraft:bed", "NoDestroyBlock"))
                isDestroy = false;
        }
    }
    return original(_this, bs, actor, pos, power, isFire, isDestroy, range, a9);
}

// ===== onRespawnAnchorExplode =====
THook(void, "?explode@RespawnAnchorBlock@@CAXAEAVPlayer@@AEBVBlockPos@@AEAVBlockSource@@AEAVLevel@@@Z",
    void* _this, Player* pl, BlockPos* bp, BlockSource* bs, Level* level)
{
    if (!suspend && ini.GetBoolValue("minecraft:respawn_anchor", "NoExplosion"))
        return;
    return original(_this, pl, bp, bs, level);
}

// ===== onWitherBossDestroy =====
THook(void, "?_destroyBlocks@WitherBoss@@AEAAXAEAVLevel@@AEBVAABB@@AEAVBlockSource@@H@Z",
    void* _this, Level* a2, AABB* a3, BlockSource* a4, int a5)
{
    if (ini.GetBoolValue("minecraft:wither", "NoDestroyBlock"))
        return;
    original(_this, a2, a3, a4, a5);
}

// ===== onWitherBossDestroy =====
THook(bool, "?canDestroy@WitherBoss@@SA_NAEBVBlock@@@Z",
    Block *bl)
{
    if (ini.GetBoolValue("minecraft:wither", "NoDestroyBlock"))
        return false;
    return original(bl);
}



// 命令
enum EXPOP :int {
    off = 1,
    on = 2,
    reload = 3
};

bool ReloadIni()
{
    ini.Reset();
    return ini.LoadFile(_CONF_PATH) == 0;
}

bool ChangeExpRule(CommandOrigin const& ori, CommandOutput& outp, MyEnum<EXPOP> op)
{
    switch (op)
    {
    case off:
        suspend = true;
        cout << "=== 自定义防爆规则已临时关闭 ===" << endl;
        break;
    case on:
        suspend = false;
        cout << "=== 自定义防爆规则已启用 ===" << endl;
        break;
    case reload:
        if (ReloadIni())
            cout << "配置文件已重新加载。" << endl;
        else
            cout << "配置文件解析失败！插件将不会正常工作" << endl;
        break;
    default:
        cout << "未知操作！" << endl;
        return false;
    }
    return true;
}


// Main

void entry()
{
    ini.SetUnicode(true);
    auto res = ini.LoadFile(_CONF_PATH);
    if (res < 0)
    {
        cerr << "[BanExplosion] 防爆插件加载配置文件失败！" << endl;
        cerr << "[BanExplosion] 插件将不会正常工作。" << endl;
        return;
    }

    Event::addEventListener([](RegCmdEV ev)
    {
        CMDREG::SetCommandRegistry(ev.CMDRg);
        MakeCommand("banexp", "Control custom explosion rule", 4);
        CEnum<EXPOP> _1("operation", { "off","on","reload" });
        CmdOverload(banexp, ChangeExpRule, "operation");
    });

    std::cout << "[BanExplosion] BanExplosion自定义防爆插件-已装载  当前版本：" << _VER << endl;
    std::cout << "[BanExplosion] 配置文件位于：" << _CONF_PATH << endl;
    std::cout << "[BanExplosion] 作者：yqs112358   首发平台：MineBBS" << endl;
    std::cout << "[BanExplosion] 欲联系作者可前往MineBBS论坛" << endl;
}