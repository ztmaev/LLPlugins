#include "pch.h"
#include "headers/api/commands.h"
#include "headers/api/types/types.h"
#include "headers/loader/Loader.h"
#include "headers/mc/Player.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

void entry()
{
    std::cout << "[DimTP] DimTP loaded." << endl;
    std::cout << "[DimTP] Usage: dimtp playername x y z dimid" << endl;
    std::cout << "[DimTP] If playername containes space like 'player name'," << endl;
    std::cout << "[DimTP] Use: dimtp \"player name\" x y z dimid" << endl;
}


vector<Player*> GetOnlinePlayers()
{
    return liteloader::getAllPlayers();
}

vector<string> SplitCmdLine(const string& paras)
{
    vector<string> res;
    string now, strInQuote = "";
    istringstream strIn(paras);
    while (strIn >> now)
    {
        if (!strInQuote.empty())
        {
            strInQuote = strInQuote + " " + now;
            if (now.back() == '\"')
            {
                strInQuote.pop_back();
                res.push_back(strInQuote.erase(0, 1));
                strInQuote = "";
            }
        }
        else
        {
            if (now.front() == '\"')
                strInQuote = now;
            else
                res.push_back(now);
        }
    }
    if (!strInQuote.empty())
    {
        istringstream leftIn(strInQuote);
        while (leftIn >> now)
            res.push_back(now);
    }
    return res;
}

string  GetPlayerName(Player* player)
{
    return player->getNameTag();
}

bool Dimtp(Player* player, float x, float y, float z, int dim)
{
    WPlayer(*player).teleport({ x,y,z }, dim);
    return true;
}

THook(bool, "?executeCommand@MinecraftCommands@@QEBA?AUMCRESULT@@V?$shared_ptr@VCommandContext@@@std@@_N@Z",
    MinecraftCommands* _this, unsigned int* a2, std::shared_ptr<CommandContext> x, char a4)
{
    Player* player = MakeSP(x->getOrigin());
    if (!player)
    {
        // Server Command
        string cmd = x->getCmd();
        if (cmd.find("/dimtp") == 0)
        {
            auto cmds = SplitCmdLine(cmd);
            if (cmds.size() >= 6)
            {
                auto players = GetOnlinePlayers();
                for (auto& pl : players)
                {
                    if (GetPlayerName(pl) == cmds[1])   //name
                    {
                        Dimtp(pl, stoi(cmds[2]), stoi(cmds[3]), stoi(cmds[4]), stoi(cmds[5]));      //x,y,z,dim
                        return false;
                    }
                }
            }
        }
    }
    return original(_this, a2, x, a4);
}