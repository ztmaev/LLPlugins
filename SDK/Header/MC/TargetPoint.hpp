// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"

#define BEFORE_EXTRA

#undef BEFORE_EXTRA

struct TargetPoint {

#define AFTER_EXTRA

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_TARGETPOINT
public:
    struct TargetPoint& operator=(struct TargetPoint const&) = delete;
    TargetPoint(struct TargetPoint const&) = delete;
    TargetPoint() = delete;
#endif

public:
    MCAPI TargetPoint(float, float, float, float, float, float);

protected:

private:

};