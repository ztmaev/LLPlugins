// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "Feature.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class ReedsFeature : public Feature {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_REEDSFEATURE
public:
    class ReedsFeature& operator=(class ReedsFeature const&) = delete;
    ReedsFeature(class ReedsFeature const&) = delete;
    ReedsFeature() = delete;
#endif

public:
    /*0*/ virtual ~ReedsFeature();
    /*1*/ virtual void __unk_vfn_0();
    /*2*/ virtual bool place(class BlockSource&, class BlockPos const&, class Random&) const;

protected:

private:

};