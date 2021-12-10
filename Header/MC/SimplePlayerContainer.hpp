// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "SimpleContainer.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class SimplePlayerContainer : public SimpleContainer {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_SIMPLEPLAYERCONTAINER
public:
    class SimplePlayerContainer& operator=(class SimplePlayerContainer const&) = delete;
    SimplePlayerContainer(class SimplePlayerContainer const&) = delete;
    SimplePlayerContainer() = delete;
#endif

public:
    /*0*/ virtual ~SimplePlayerContainer();
    /*1*/ virtual void init();
    /*2*/ virtual void setItem(int, class ItemStack const&);
    /*3*/ virtual int getContainerSize() const;
    /*4*/ virtual int getMaxStackSize() const;
    /*5*/ virtual void startOpen(class Player&);
    /*6*/ virtual void stopOpen(class Player&);
    /*7*/ virtual void __unk_vfn_0();
    /*8*/ virtual void __unk_vfn_1();
    /*9*/ virtual void __unk_vfn_2();
    MCAPI SimplePlayerContainer(class Player&, std::string const&, bool, int, enum ContainerType);

protected:

private:

};