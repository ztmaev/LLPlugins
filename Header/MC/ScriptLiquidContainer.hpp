// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "Scripting.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class ScriptLiquidContainer {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_SCRIPTLIQUIDCONTAINER
public:
    class ScriptLiquidContainer& operator=(class ScriptLiquidContainer const&) = delete;
    ScriptLiquidContainer(class ScriptLiquidContainer const&) = delete;
    ScriptLiquidContainer() = delete;
#endif

public:
    MCAPI static class Scripting::ClassBindingBuilder<class ScriptLiquidContainer> bind(struct Scripting::Version);

protected:

private:

};