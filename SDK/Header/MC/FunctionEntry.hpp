// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class FunctionEntry {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_FUNCTIONENTRY
public:
    class FunctionEntry& operator=(class FunctionEntry const&) = delete;
    FunctionEntry(class FunctionEntry const&) = delete;
    FunctionEntry() = delete;
#endif

public:
    /*0*/ virtual ~FunctionEntry();
    /*1*/ virtual void execute(class FunctionManager&, class CommandOrigin const&);
    MCAPI enum FunctionState getErrorState() const;

protected:

private:

};