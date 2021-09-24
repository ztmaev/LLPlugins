#include "pch.h"
#include "headers/lbpch.h"
#include "headers/mc/OffsetHelper.h"
//#include "headers/api/Basic_Event.h"
#include <string>
#include <Windows.h>
#include <stdlib.h>
#include "SimpleIni.h"
using namespace std;

#define _VER "1.0.0"
#define _CONF_PATH "plugins/BetterStop/config.ini"

CSimpleIniA ini;
bool isStopping = false;
bool isServerStarted = false;
Minecraft* mc;

//Utils

vector<Player*> Raw_GetOnlinePlayers()
{
    vector<Player*> pls;
    if (isServerStarted)
        pls = liteloader::getAllPlayers();

    return pls;
}

bool Raw_KickPlayer(Player* player, const string& msg)
{
    auto nh = mc->getServerNetworkHandler();
    NetworkIdentifier* a = offPlayer::getNetworkIdentifier(player);
    nh->disconnectClient(*(NetworkIdentifier*)a, msg, 0);
    return true;
}

bool Raw_Runcmd(const string& cmd)
{
    return liteloader::runcmd(cmd);
}

THook(void, "?initAsDedicatedServer@Minecraft@@QEAAXXZ",
    void* self)
{
    original(self);
    mc = (Minecraft*)self;
}


// Main

void SafeStop()
{
    if (isStopping)
        return;
    isStopping = true;

    cout << "[BetterStop] Safe Stop processing..." << endl;
    auto players = Raw_GetOnlinePlayers();
    for (auto& pl : players)
    {
        Raw_KickPlayer(pl, string(ini.GetValue("Main", "StopMsg", "Server stopping...")));
    }
    Raw_Runcmd("stop");
}

// ===== onConsoleCmd =====
THook(bool, "??$inner_enqueue@$0A@AEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@?$SPSCQueue@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@$0CAA@@@AEAA_NAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z",
    void* _this, string &cmd)
{
    if (cmd.front() == '/')
        cmd = cmd.substr(1);
    if (!cmd.empty() && cmd == "stop" && !isStopping)
    {
        SafeStop();
        return false;
    }
    return original(_this, cmd);
}

//Message
BOOL CtrlHandler(DWORD fdwCtrlType)
{
    switch (fdwCtrlType)
    {
    case CTRL_C_EVENT:
    case CTRL_CLOSE_EVENT:
    case CTRL_SHUTDOWN_EVENT:
        cout << "[BetterStop] Stop detected." << endl;
        SafeStop();
        return TRUE;

    case CTRL_BREAK_EVENT:
    case CTRL_LOGOFF_EVENT:
        return FALSE;

    default:
        return FALSE;
    }
}

//Main
void entry(HMODULE hMod)
{
    if (!SetConsoleCtrlHandler((PHANDLER_ROUTINE)CtrlHandler, TRUE))
        cerr << "[BetterStop] Fail to enable Console Close Protection!" << endl;

    HWND hwnd = GetConsoleWindow();
    HMENU hmenu = GetSystemMenu(hwnd, false);
    RemoveMenu(hmenu, SC_CLOSE, MF_BYCOMMAND);
    DestroyMenu(hmenu);
    ReleaseDC(hwnd, NULL);

    Event::addEventListener([](ServerStartedEV ev)
    {
        isServerStarted = true;
    });

    ini.SetUnicode(true);
    auto res = ini.LoadFile(_CONF_PATH);

    std::cout << "[BetterStop] BetterStop 关服保护插件-已装载  当前版本：" << _VER << endl;
}