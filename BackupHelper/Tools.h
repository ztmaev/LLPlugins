#pragma once
#include "pch.h"
#include <string>
#include <iostream>
#include <string>
#include <exception>
using namespace std;

inline void ErrorOutput(const string& e)
{
    cerr << "[BackupHelper] " << e << endl;
}

inline bool Raw_Tell(Player* player, const std::string& text, TextType type)
{
    WPlayer(*player).sendText(text, type);
    return true;
}

inline void SendFeedback(Player* p, const string& msg)
{
    auto pls = liteloader::getAllPlayers();
    bool found = false;
    for (auto& pl : pls)
    {
        if (pl == p)
        {
            found = true;
            break;
        }
    }
    if (!found)
    {
        extern Player* nowPlayer;
        nowPlayer = p = nullptr;
    }

    if (!p)
        std::cout << "[BackupHelper] " << msg << std::endl;
    else
    {
        try
        {
            Raw_Tell(p, "§e[BackupHelper]§r " + msg, TextType::RAW);
        }
        catch (const seh_exception&)
        {
            extern Player* nowPlayer;
            nowPlayer = nullptr;
            std::cout << "[BackupHelper] " << msg << std::endl;
        }
        catch (const exception&)
        {
            extern Player* nowPlayer;
            nowPlayer = nullptr;
            std::cout << "[BackupHelper] " << msg << std::endl;
        }
    }
}

inline wstring U8StringToWString(const string& u8str)
{
    int targetLen = MultiByteToWideChar(CP_UTF8, 0, u8str.c_str(), -1, NULL, 0);
    if (targetLen == ERROR_NO_UNICODE_TRANSLATION || targetLen == 0)
        return L"";
    wchar_t* res = new wchar_t[targetLen + 1];
    ZeroMemory(res, sizeof(wchar_t) * (targetLen + 1));
    size_t resLen = MultiByteToWideChar(CP_UTF8, 0, u8str.c_str(), -1, res, targetLen);
    wstring resStr = wstring(res);

    delete[] res;
    return resStr;
}