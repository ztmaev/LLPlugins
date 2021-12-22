// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class EmptyPlayerGameplayHandler {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_EMPTYPLAYERGAMEPLAYHANDLER
public:
    class EmptyPlayerGameplayHandler& operator=(class EmptyPlayerGameplayHandler const&) = delete;
    EmptyPlayerGameplayHandler(class EmptyPlayerGameplayHandler const&) = delete;
    EmptyPlayerGameplayHandler() = delete;
#endif

public:
    /*0*/ virtual ~EmptyPlayerGameplayHandler();
    /*
    inline enum HandlerResult handleAddExp(struct PlayerAddExpEvent const& a0){
        enum HandlerResult (EmptyPlayerGameplayHandler::*rv)(struct PlayerAddExpEvent const&);
        *((void**)&rv) = dlsym("?handleAddExp@EmptyPlayerGameplayHandler@@UEAA?AW4HandlerResult@@AEBUPlayerAddExpEvent@@@Z");
        return (this->*rv)(std::forward<struct PlayerAddExpEvent const&>(a0));
    }
    inline enum HandlerResult handleRespawn(struct PlayerEvent const& a0){
        enum HandlerResult (EmptyPlayerGameplayHandler::*rv)(struct PlayerEvent const&);
        *((void**)&rv) = dlsym("?handleRespawn@EmptyPlayerGameplayHandler@@UEAA?AW4HandlerResult@@AEBUPlayerEvent@@@Z");
        return (this->*rv)(std::forward<struct PlayerEvent const&>(a0));
    }
    inline enum HandlerResult handleShootArrow(struct PlayerShootArrowEvent const& a0){
        enum HandlerResult (EmptyPlayerGameplayHandler::*rv)(struct PlayerShootArrowEvent const&);
        *((void**)&rv) = dlsym("?handleShootArrow@EmptyPlayerGameplayHandler@@UEAA?AW4HandlerResult@@AEBUPlayerShootArrowEvent@@@Z");
        return (this->*rv)(std::forward<struct PlayerShootArrowEvent const&>(a0));
    }
    inline enum HandlerResult handleAddLevel(struct PlayerAddLevelEvent const& a0){
        enum HandlerResult (EmptyPlayerGameplayHandler::*rv)(struct PlayerAddLevelEvent const&);
        *((void**)&rv) = dlsym("?handleAddLevel@EmptyPlayerGameplayHandler@@UEAA?AW4HandlerResult@@AEBUPlayerAddLevelEvent@@@Z");
        return (this->*rv)(std::forward<struct PlayerAddLevelEvent const&>(a0));
    }
    inline enum HandlerResult handleAddPlayer(struct PlayerEvent const& a0){
        enum HandlerResult (EmptyPlayerGameplayHandler::*rv)(struct PlayerEvent const&);
        *((void**)&rv) = dlsym("?handleAddPlayer@EmptyPlayerGameplayHandler@@UEAA?AW4HandlerResult@@AEBUPlayerEvent@@@Z");
        return (this->*rv)(std::forward<struct PlayerEvent const&>(a0));
    }
    inline enum HandlerResult handleEatFood(struct PlayerEatFoodEvent const& a0){
        enum HandlerResult (EmptyPlayerGameplayHandler::*rv)(struct PlayerEatFoodEvent const&);
        *((void**)&rv) = dlsym("?handleEatFood@EmptyPlayerGameplayHandler@@UEAA?AW4HandlerResult@@AEBUPlayerEatFoodEvent@@@Z");
        return (this->*rv)(std::forward<struct PlayerEatFoodEvent const&>(a0));
    }
    inline enum HandlerResult handleUseNameTag(struct PlayerUseNameTagEvent const& a0){
        enum HandlerResult (EmptyPlayerGameplayHandler::*rv)(struct PlayerUseNameTagEvent const&);
        *((void**)&rv) = dlsym("?handleUseNameTag@EmptyPlayerGameplayHandler@@UEAA?AW4HandlerResult@@AEBUPlayerUseNameTagEvent@@@Z");
        return (this->*rv)(std::forward<struct PlayerUseNameTagEvent const&>(a0));
    }
    inline enum HandlerResult handleDestroyBlock(struct PlayerDestroyBlockEvent const& a0){
        enum HandlerResult (EmptyPlayerGameplayHandler::*rv)(struct PlayerDestroyBlockEvent const&);
        *((void**)&rv) = dlsym("?handleDestroyBlock@EmptyPlayerGameplayHandler@@UEAA?AW4HandlerResult@@AEBUPlayerDestroyBlockEvent@@@Z");
        return (this->*rv)(std::forward<struct PlayerDestroyBlockEvent const&>(a0));
    }
    inline enum HandlerResult handleUpdateInteraction(struct PlayerUpdateInteractionEvent const& a0){
        enum HandlerResult (EmptyPlayerGameplayHandler::*rv)(struct PlayerUpdateInteractionEvent const&);
        *((void**)&rv) = dlsym("?handleUpdateInteraction@EmptyPlayerGameplayHandler@@UEAA?AW4HandlerResult@@AEBUPlayerUpdateInteractionEvent@@@Z");
        return (this->*rv)(std::forward<struct PlayerUpdateInteractionEvent const&>(a0));
    }
    inline enum HandlerResult handleStopLoading(struct PlayerEvent const& a0){
        enum HandlerResult (EmptyPlayerGameplayHandler::*rv)(struct PlayerEvent const&);
        *((void**)&rv) = dlsym("?handleStopLoading@EmptyPlayerGameplayHandler@@UEAA?AW4HandlerResult@@AEBUPlayerEvent@@@Z");
        return (this->*rv)(std::forward<struct PlayerEvent const&>(a0));
    }
    inline enum HandlerResult handleArmorExchange(struct PlayerArmorExchangeEvent const& a0){
        enum HandlerResult (EmptyPlayerGameplayHandler::*rv)(struct PlayerArmorExchangeEvent const&);
        *((void**)&rv) = dlsym("?handleArmorExchange@EmptyPlayerGameplayHandler@@UEAA?AW4HandlerResult@@AEBUPlayerArmorExchangeEvent@@@Z");
        return (this->*rv)(std::forward<struct PlayerArmorExchangeEvent const&>(a0));
    }
    inline enum HandlerResult handleDimensionChange(struct PlayerDimensionChangeEvent const& a0){
        enum HandlerResult (EmptyPlayerGameplayHandler::*rv)(struct PlayerDimensionChangeEvent const&);
        *((void**)&rv) = dlsym("?handleDimensionChange@EmptyPlayerGameplayHandler@@UEAA?AW4HandlerResult@@AEBUPlayerDimensionChangeEvent@@@Z");
        return (this->*rv)(std::forward<struct PlayerDimensionChangeEvent const&>(a0));
    }
    inline enum HandlerResult handleDie(struct PlayerDamageEvent const& a0){
        enum HandlerResult (EmptyPlayerGameplayHandler::*rv)(struct PlayerDamageEvent const&);
        *((void**)&rv) = dlsym("?handleDie@EmptyPlayerGameplayHandler@@UEAA?AW4HandlerResult@@AEBUPlayerDamageEvent@@@Z");
        return (this->*rv)(std::forward<struct PlayerDamageEvent const&>(a0));
    }
    inline enum HandlerResult handlePlayerOpenContainer(struct PlayerOpenContainerEvent const& a0){
        enum HandlerResult (EmptyPlayerGameplayHandler::*rv)(struct PlayerOpenContainerEvent const&);
        *((void**)&rv) = dlsym("?handlePlayerOpenContainer@EmptyPlayerGameplayHandler@@UEAA?AW4HandlerResult@@AEBUPlayerOpenContainerEvent@@@Z");
        return (this->*rv)(std::forward<struct PlayerOpenContainerEvent const&>(a0));
    }
    inline enum HandlerResult handleHurt(struct PlayerDamageEvent const& a0){
        enum HandlerResult (EmptyPlayerGameplayHandler::*rv)(struct PlayerDamageEvent const&);
        *((void**)&rv) = dlsym("?handleHurt@EmptyPlayerGameplayHandler@@UEAA?AW4HandlerResult@@AEBUPlayerDamageEvent@@@Z");
        return (this->*rv)(std::forward<struct PlayerDamageEvent const&>(a0));
    }
    inline enum HandlerResult handleSelectedItemChanged(struct PlayerSelectedItemChangedEvent const& a0){
        enum HandlerResult (EmptyPlayerGameplayHandler::*rv)(struct PlayerSelectedItemChangedEvent const&);
        *((void**)&rv) = dlsym("?handleSelectedItemChanged@EmptyPlayerGameplayHandler@@UEAA?AW4HandlerResult@@AEBUPlayerSelectedItemChangedEvent@@@Z");
        return (this->*rv)(std::forward<struct PlayerSelectedItemChangedEvent const&>(a0));
    }
    inline enum HandlerResult handleDropItem(struct PlayerDropItemEvent const& a0){
        enum HandlerResult (EmptyPlayerGameplayHandler::*rv)(struct PlayerDropItemEvent const&);
        *((void**)&rv) = dlsym("?handleDropItem@EmptyPlayerGameplayHandler@@UEAA?AW4HandlerResult@@AEBUPlayerDropItemEvent@@@Z");
        return (this->*rv)(std::forward<struct PlayerDropItemEvent const&>(a0));
    }
    inline struct GameplayHandlerResult<enum CoordinatorResult> handleGetExperienceOrb(struct PlayerGetExperienceOrbEvent const& a0){
        struct GameplayHandlerResult<enum CoordinatorResult> (EmptyPlayerGameplayHandler::*rv)(struct PlayerGetExperienceOrbEvent const&);
        *((void**)&rv) = dlsym("?handleGetExperienceOrb@EmptyPlayerGameplayHandler@@UEAA?AU?$GameplayHandlerResult@W4CoordinatorResult@@@@AEBUPlayerGetExperienceOrbEvent@@@Z");
        return (this->*rv)(std::forward<struct PlayerGetExperienceOrbEvent const&>(a0));
    }
    inline struct GameplayHandlerResult<enum CoordinatorResult> handleInteract(struct PlayerInteractEvent const& a0){
        struct GameplayHandlerResult<enum CoordinatorResult> (EmptyPlayerGameplayHandler::*rv)(struct PlayerInteractEvent const&);
        *((void**)&rv) = dlsym("?handleInteract@EmptyPlayerGameplayHandler@@UEAA?AU?$GameplayHandlerResult@W4CoordinatorResult@@@@AEBUPlayerInteractEvent@@@Z");
        return (this->*rv)(std::forward<struct PlayerInteractEvent const&>(a0));
    }
    inline struct GameplayHandlerResult<enum CoordinatorResult> handleSayCommand(struct PlayerSayCommandEvent const& a0){
        struct GameplayHandlerResult<enum CoordinatorResult> (EmptyPlayerGameplayHandler::*rv)(struct PlayerSayCommandEvent const&);
        *((void**)&rv) = dlsym("?handleSayCommand@EmptyPlayerGameplayHandler@@UEAA?AU?$GameplayHandlerResult@W4CoordinatorResult@@@@AEBUPlayerSayCommandEvent@@@Z");
        return (this->*rv)(std::forward<struct PlayerSayCommandEvent const&>(a0));
    }
    */

protected:

private:

};