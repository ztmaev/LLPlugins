// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class WorldSessionEndPoint {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_WORLDSESSIONENDPOINT
public:
    class WorldSessionEndPoint& operator=(class WorldSessionEndPoint const&) = delete;
    WorldSessionEndPoint(class WorldSessionEndPoint const&) = delete;
    WorldSessionEndPoint() = delete;
#endif

public:
    /*
    inline void flush(){
        void (WorldSessionEndPoint::*rv)();
        *((void**)&rv) = dlsym("?flush@WorldSessionEndPoint@@UEAAXXZ");
        return (this->*rv)();
    }
    inline bool logOnlyOnce() const{
        bool (WorldSessionEndPoint::*rv)() const;
        *((void**)&rv) = dlsym("?logOnlyOnce@WorldSessionEndPoint@@UEBA_NXZ");
        return (this->*rv)();
    }
    inline bool isEnabled() const{
        bool (WorldSessionEndPoint::*rv)() const;
        *((void**)&rv) = dlsym("?isEnabled@WorldSessionEndPoint@@UEBA_NXZ");
        return (this->*rv)();
    }
    inline void setEnabled(bool a0){
        void (WorldSessionEndPoint::*rv)(bool);
        *((void**)&rv) = dlsym("?setEnabled@WorldSessionEndPoint@@UEAAX_N@Z");
        return (this->*rv)(std::forward<bool>(a0));
    }
    inline void log(int \/*enum enum LogArea*\/ a0, int \/*enum enum LogLevel*\/ a1, char const* a2){
        void (WorldSessionEndPoint::*rv)(int \/*enum enum LogArea*\/, int \/*enum enum LogLevel*\/, char const*);
        *((void**)&rv) = dlsym("?log@WorldSessionEndPoint@@UEAAXW4LogArea@@W4LogLevel@@PEBD@Z");
        return (this->*rv)(std::forward<int \/*enum enum LogArea*\/>(a0), std::forward<int \/*enum enum LogLevel*\/>(a1), std::forward<char const*>(a2));
    }
    */
    MCAPI WorldSessionEndPoint(class IMinecraftEventing&);

protected:

private:

};