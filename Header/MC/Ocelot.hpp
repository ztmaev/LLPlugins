// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "Actor.hpp"
#include "Animal.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class Ocelot : public Animal {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_OCELOT
public:
    class Ocelot& operator=(class Ocelot const&) = delete;
    Ocelot(class Ocelot const&) = delete;
    Ocelot() = delete;
#endif

public:
    /*0*/ virtual void reloadHardcoded(int /*enum enum Actor::InitializationMethod*/, class VariantParameterList const&);
    /*1*/ virtual ~Ocelot();
    /*2*/ virtual bool isRuntimePredictedMovementEnabled() const;
    /*3*/ virtual void __unk_vfn_0();
    /*4*/ virtual class Vec3 getInterpolatedRidingOffset(float) const;
    /*5*/ virtual void __unk_vfn_1();
    /*6*/ virtual float getRidingHeight();
    /*7*/ virtual void __unk_vfn_2();
    /*8*/ virtual void __unk_vfn_3();
    /*9*/ virtual float getCameraOffset() const;
    /*10*/ virtual void __unk_vfn_4();
    /*11*/ virtual void __unk_vfn_5();
    /*12*/ virtual void playerTouch(class Player&);
    /*13*/ virtual void __unk_vfn_6();
    /*14*/ virtual void __unk_vfn_7();
    /*15*/ virtual bool isDamageBlocked(class ActorDamageSource const&) const;
    /*16*/ virtual void __unk_vfn_8();
    /*17*/ virtual void __unk_vfn_9();
    /*18*/ virtual void __unk_vfn_10();
    /*19*/ virtual void __unk_vfn_11();
    /*20*/ virtual class Actor* findAttackTarget();
    /*21*/ virtual bool isValidTarget(class Actor*) const;
    /*22*/ virtual void adjustDamageAmount(int&) const;
    /*23*/ virtual void onTame();
    /*24*/ virtual void onFailedTame();
    /*25*/ virtual void vehicleLanded(class Vec3 const&, class Vec3 const&);
    /*26*/ virtual void onBounceStarted(class BlockPos const&, class Block const&);
    /*27*/ virtual float getPickRadius();
    /*28*/ virtual void awardKillScore(class Actor&, int);
    /*29*/ virtual class HashedString const& queryEntityRenderer() const;
    /*30*/ virtual struct ActorUniqueID getSourceUniqueID() const;
    /*31*/ virtual int getPortalWaitTime() const;
    /*32*/ virtual bool canChangeDimensions() const;
    /*33*/ virtual void __unk_vfn_12();
    /*34*/ virtual struct ActorUniqueID getControllingPlayer() const;
    /*35*/ virtual bool canPickupItem(class ItemStack const&) const;
    /*36*/ virtual bool canBePulledIntoVehicle() const;
    /*37*/ virtual void __unk_vfn_13();
    /*38*/ virtual bool canSynchronizeNewEntity() const;
    /*39*/ virtual void __unk_vfn_14();
    /*40*/ virtual void __unk_vfn_15();
    /*41*/ virtual bool isWorldBuilder() const;
    /*42*/ virtual void __unk_vfn_16();
    /*43*/ virtual bool isAdventure() const;
    /*44*/ virtual bool canDestroyBlock(class Block const&) const;
    /*45*/ virtual void setAuxValue(int);
    /*46*/ virtual void stopSpinAttack();
    /*47*/ virtual void __unk_vfn_17();
    /*48*/ virtual void __unk_vfn_18();
    /*49*/ virtual void updateEntitySpecificMolangVariables(class RenderParams&);
    /*50*/ virtual void __unk_vfn_19();
    /*51*/ virtual void __unk_vfn_20();
    /*52*/ virtual void __unk_vfn_21();
    /*53*/ virtual void spawnAnim();
    /*54*/ virtual int getItemUseDuration() const;
    /*55*/ virtual float getItemUseStartupProgress() const;
    /*56*/ virtual float getItemUseIntervalProgress() const;
    /*57*/ virtual void __unk_vfn_22();
    /*58*/ virtual bool isAlliedTo(class Mob*);
    /*59*/ virtual bool doHurtTarget(class Actor*, int /*enum enum ActorDamageCause*/ const&);
    /*60*/ virtual void __unk_vfn_23();
    /*61*/ virtual void sendArmorDamage(class std::bitset<4> const&);
    /*62*/ virtual void onBorn(class Actor&, class Actor&);
    /*63*/ virtual int getAttackTime();
    /*64*/ virtual void __unk_vfn_24();
    /*65*/ virtual void _serverAiMobStep();
    /*66*/ virtual void __unk_vfn_25();
    MCAPI Ocelot(class ActorDefinitionGroup*, struct ActorDefinitionIdentifier const&, class OwnerPtrT<struct EntityRefTraits> const&);
    MCAPI static float const SNEAK_SPEED_MOD;
    MCAPI static float const SPRINT_SPEED_MOD;

protected:

private:

};