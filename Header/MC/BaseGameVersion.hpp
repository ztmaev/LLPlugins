// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "SemVersion.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class BaseGameVersion {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

public:
    MCAPI BaseGameVersion(class BaseGameVersion const&);
    MCAPI BaseGameVersion(class SemVersion const&);
    MCAPI BaseGameVersion(unsigned short, unsigned int, unsigned int);
    MCAPI BaseGameVersion();
    MCAPI class SemVersion const& asSemVersion() const;
    MCAPI std::string const& asString() const;
    MCAPI unsigned short getMajor() const;
    MCAPI unsigned short getMinor() const;
    MCAPI unsigned short getPatch() const;
    MCAPI bool isAnyVersion() const;
    MCAPI bool isCompatibleWith(class BaseGameVersion const&) const;
    MCAPI bool isValid() const;
    MCAPI bool operator<(class BaseGameVersion const&);
    MCAPI bool operator<=(class BaseGameVersion const&);
    MCAPI class BaseGameVersion& operator=(class BaseGameVersion const&);
    MCAPI bool operator==(class BaseGameVersion const&);
    MCAPI bool operator>(class BaseGameVersion const&);
    MCAPI bool operator>=(class BaseGameVersion const&);
    MCAPI ~BaseGameVersion();
    MCAPI static class BaseGameVersion const ANY;
    MCAPI static class BaseGameVersion const EMPTY;
    MCAPI static class BaseGameVersion const INCOMPATIBLE;
    MCAPI static enum SemVersion::MatchType fromString(std::string const&, class BaseGameVersion&);

protected:

private:

};