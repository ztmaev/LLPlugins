#include "pch.h"
#include <loader/Loader.h>
#include <iostream>
#include <string>
#include <variant>


void entry()
{
    std::cout << "[FixBeacon] Bug in Beacon fixed." << std::endl;
}


class Player;

THook(char, "?_handleTransfer@ItemStackRequestActionHandler@@AEAA?AW4ItemStackNetResult@@AEBVItemStackRequestActionTransferBase@@_N11@Z",
    void* _this, void* base, bool b1, bool b2, bool b3)
{
    try {
        if ((int)dAccess<char>(base, 8) == 0 && dAccess<bool>(base, 16) &&
            dAccess<char>(base, 20) != dAccess<char>(base, 32) &&
            dAccess<int>(base, 24) == dAccess<int>(base, 36))
        {
            return 0;
        }
    }
    catch (const std::bad_variant_access& e)
    {
        std::cout << "[Error] " << e.what() << std::endl;
    }
    return original(_this, base, b1, b2, b3);
}
