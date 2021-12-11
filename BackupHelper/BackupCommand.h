#pragma once
//#define LEGACY_COMMAND

#ifdef LEGACY_COMMAND
#include "../Header/MC/CommandRegistry.hpp"
#include "../Header/MC/CommandParameterData.hpp"

#else
#include "../Header/RegCommandAPI.h"

class BackupCommand : public Command {
    enum class BackupOP :int {
        reload,
        cancel,
    } op;
    bool op_isSet = false;

    virtual void execute(CommandOrigin const& ori, CommandOutput& outp) const;
public:
    static void setup(CommandRegistry* registry);
};

#endif // LEGACY_COMMAND