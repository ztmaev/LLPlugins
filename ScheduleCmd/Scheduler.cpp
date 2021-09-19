#include "pch.h"
#include <libcron/Cron.h>
#include <ctime>
#include <queue>
#include <string>
#include <windows.h> 
#include <iostream>
#include <vector>
using namespace libcron;
using namespace std;

static int taskid = 0;
libcron::Cron cron;


// 植入tick
THook(void, "?tick@ServerLevel@@UEAAXXZ",
    void* _this)
{
    cron.tick();
    return original(_this);
}

bool AddSchedule(string cmd, string cronStr)
{
    cron.add_schedule(cmd + to_string(++taskid), cronStr, [cmd](auto&) {
        Handler::scheduleNext([cmd]() {
            liteloader::runcmd(cmd);
        });
    });
    return true;
}

bool RemoveSchedule(string cmd)
{
    return true;
}

bool RemoveAllSchedule()
{
    cron.clear_schedules();
    return true;
}