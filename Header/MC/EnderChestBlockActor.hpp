// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class EnderChestBlockActor {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_ENDERCHESTBLOCKACTOR
public:
    class EnderChestBlockActor& operator=(class EnderChestBlockActor const&) = delete;
    EnderChestBlockActor(class EnderChestBlockActor const&) = delete;
    EnderChestBlockActor() = delete;
#endif

public:
    /*
    inline bool canPushInItem(class BlockSource& a0, int a1, int a2, class ItemInstance const& a3) const{
        bool (EnderChestBlockActor::*rv)(class BlockSource&, int, int, class ItemInstance const&) const;
        *((void**)&rv) = dlsym("?canPushInItem@EnderChestBlockActor@@UEBA_NAEAVBlockSource@@HHAEBVItemInstance@@@Z");
        return (this->*rv)(std::forward<class BlockSource&>(a0), std::forward<int>(a1), std::forward<int>(a2), std::forward<class ItemInstance const&>(a3));
    }
    inline bool canPullOutItem(class BlockSource& a0, int a1, int a2, class ItemInstance const& a3) const{
        bool (EnderChestBlockActor::*rv)(class BlockSource&, int, int, class ItemInstance const&) const;
        *((void**)&rv) = dlsym("?canPullOutItem@EnderChestBlockActor@@UEBA_NAEAVBlockSource@@HHAEBVItemInstance@@@Z");
        return (this->*rv)(std::forward<class BlockSource&>(a0), std::forward<int>(a1), std::forward<int>(a2), std::forward<class ItemInstance const&>(a3));
    }
    inline std::string getName() const{
        std::string (EnderChestBlockActor::*rv)() const;
        *((void**)&rv) = dlsym("?getName@EnderChestBlockActor@@UEBA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
        return (this->*rv)();
    }
    inline void playCloseSound(class BlockSource& a0){
        void (EnderChestBlockActor::*rv)(class BlockSource&);
        *((void**)&rv) = dlsym("?playCloseSound@EnderChestBlockActor@@MEAAXAEAVBlockSource@@@Z");
        return (this->*rv)(std::forward<class BlockSource&>(a0));
    }
    inline void playOpenSound(class BlockSource& a0){
        void (EnderChestBlockActor::*rv)(class BlockSource&);
        *((void**)&rv) = dlsym("?playOpenSound@EnderChestBlockActor@@MEAAXAEAVBlockSource@@@Z");
        return (this->*rv)(std::forward<class BlockSource&>(a0));
    }
    */

protected:

private:
    MCAPI static int const ITEMS_SIZE;

};