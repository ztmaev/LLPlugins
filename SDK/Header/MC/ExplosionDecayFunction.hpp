// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "LootItemFunction.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class ExplosionDecayFunction : public LootItemFunction {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_EXPLOSIONDECAYFUNCTION
public:
    class ExplosionDecayFunction& operator=(class ExplosionDecayFunction const&) = delete;
    ExplosionDecayFunction(class ExplosionDecayFunction const&) = delete;
    ExplosionDecayFunction() = delete;
#endif

public:
    /*0*/ virtual ~ExplosionDecayFunction();
    /*1*/ virtual void apply(class ItemStack&, class Random&, class LootTableContext&);
    /*3*/ virtual void apply(class ItemInstance&, class Random&, class LootTableContext&);

protected:

private:

};