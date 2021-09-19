#pragma once
#include "pch.h"
#include <string>
#include <iostream>
#include <string>
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
    if (!p)
        std::cout << "[BackupHelper] " << msg << std::endl;
    else
    {
        DelayedTask task([p, msg]() {
            try
            {
                Raw_Tell(p, "<BackupHelper> " + msg, TextType::SYSTEM);
            }
            catch (const seh_exception&)
            {
                extern Player* nowPlayer;
                nowPlayer = nullptr;
                std::cout << "[BackupHelper] " << msg << std::endl;
            }
        }, 1);
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