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

inline wstring str2wstr(string str) {
    auto len = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
    wchar_t* buffer = new wchar_t[len + 1];
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, buffer, len + 1);
    buffer[len] = L'\0';

    wstring result = wstring(buffer);
    delete[] buffer;
    return result;
}

inline string wstr2str(wstring wstr) {
    auto  len = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, NULL, 0, NULL, NULL);
    char* buffer = new char[len + 1];
    WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, buffer, len + 1, NULL, NULL);
    buffer[len] = '\0';

    string result = string(buffer);
    delete[] buffer;
    return result;
}