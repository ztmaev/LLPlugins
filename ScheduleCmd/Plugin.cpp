#include "pch.h"
#include "ConfigFile.h"
#include <EventAPI.h>
#include <Global.h>
using namespace std;

class CommandRegistry;
bool RegisterCmd(CommandRegistry *reg, const string& cmd, const string& describe, int cmdLevel)
{
    SymCall("?registerCommand@CommandRegistry@@QEAAXAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PEBDW4CommandPermissionLevel@@UCommandFlag@@3@Z",
        void, void*, const string&, const char*, char, char, char)
        (reg, cmd, describe.c_str(), cmdLevel, 0, 0x40);
    return true;
}

void RegisterCmdProcess();

Logger logger("ScheduleCmd");

void entry()
{
    std::cout << "[ScheduleCmd] ScheduleCmd 计划命令已加载！" << endl;
    std::cout << "[ScheduleCmd] 配置文件位于：plugins/ScheduleCmd/schedule.json" << endl;
    std::cout << "[ScheduleCmd] 在后台使用 /schedule 命令来设置命令定时执行计划" << endl;

    Event::ServerStartedEvent::subscribe([](const Event::ServerStartedEvent& ev) {
        LoadConfigFile(CONFIG_PATH);
        std::cout << "[ScheduleCmd] 计划命令系统已开始计时" << endl;
        return true;
    });

    Event::RegCmdEvent::subscribe([](const Event::RegCmdEvent &ev) {
        RegisterCmd(ev.mCommandRegistry, "schedulecmd", "Manage schedules of command execute", 4);
        return true;
    });
    RegisterCmdProcess();
}