// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "Json.hpp"
#include "ActorServerCommandOrigin.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class GameDirectorEntityServerCommandOrigin : public ActorServerCommandOrigin {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_GAMEDIRECTORENTITYSERVERCOMMANDORIGIN
public:
    class GameDirectorEntityServerCommandOrigin& operator=(class GameDirectorEntityServerCommandOrigin const&) = delete;
    GameDirectorEntityServerCommandOrigin(class GameDirectorEntityServerCommandOrigin const&) = delete;
    GameDirectorEntityServerCommandOrigin() = delete;
#endif

public:
    /*0*/ virtual ~GameDirectorEntityServerCommandOrigin();
    /*1*/ virtual std::string const& getRequestId() const;
    /*2*/ virtual class Level* getLevel() const;
    /*3*/ virtual int /*enum enum CommandPermissionLevel*/ getPermissionsLevel() const;
    /*4*/ virtual std::unique_ptr<class CommandOrigin> clone() const;
    /*5*/ virtual class std::optional<class BlockPos> getCursorHitBlockPos() const;
    /*6*/ virtual class std::optional<class Vec3> getCursorHitPos() const;
    /*7*/ virtual bool canUseAbility(int /*enum enum AbilitiesIndex*/) const;
    /*8*/ virtual bool canUseCommandsWithoutCheatsEnabled() const;
    /*9*/ virtual bool isSelectorExpansionAllowed() const;
    /*10*/ virtual unsigned char getSourceSubId() const;
    /*11*/ virtual class CommandOrigin const& getOutputReceiver() const;
    /*12*/ virtual int /*enum enum CommandOriginType*/ getOriginType() const;
    /*13*/ virtual class mce::UUID const& getUUID() const;
    /*14*/ virtual void handleCommandOutputCallback(class Json::Value&&) const;
    /*15*/ virtual bool isValid() const;
    MCAPI GameDirectorEntityServerCommandOrigin(class Actor&);
    MCAPI GameDirectorEntityServerCommandOrigin(struct ActorUniqueID, class Level&);
    MCAPI static std::unique_ptr<class GameDirectorEntityServerCommandOrigin> load(class CompoundTag const&, class Level&);

protected:

private:

};