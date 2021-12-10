// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "Actor.hpp"
#include "Monster.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class Witch : public Monster {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_WITCH
public:
    class Witch& operator=(class Witch const&) = delete;
    Witch(class Witch const&) = delete;
    Witch() = delete;
#endif

public:
    /*0*/ virtual ~Witch();
    /*1*/ virtual bool isRuntimePredictedMovementEnabled() const;
    /*2*/ virtual void __unk_vfn_0();
    /*3*/ virtual class Vec3 getInterpolatedRidingOffset(float) const;
    /*4*/ virtual void __unk_vfn_1();
    /*5*/ virtual float getRidingHeight();
    /*6*/ virtual void __unk_vfn_2();
    /*7*/ virtual void __unk_vfn_3();
    /*8*/ virtual float getCameraOffset() const;
    /*9*/ virtual void __unk_vfn_4();
    /*10*/ virtual void __unk_vfn_5();
    /*11*/ virtual void playerTouch(class Player&);
    /*12*/ virtual void __unk_vfn_6();
    /*13*/ virtual void __unk_vfn_7();
    /*14*/ virtual bool isDamageBlocked(class ActorDamageSource const&) const;
    /*15*/ virtual void __unk_vfn_8();
    /*16*/ virtual void __unk_vfn_9();
    /*17*/ virtual void __unk_vfn_10();
    /*18*/ virtual void __unk_vfn_11();
    /*19*/ virtual bool canAttack(class Actor*, bool) const;
    /*20*/ virtual bool isValidTarget(class Actor*) const;
    /*21*/ virtual void performRangedAttack(class Actor&, float);
    /*22*/ virtual void adjustDamageAmount(int&) const;
    /*23*/ virtual void onTame();
    /*24*/ virtual void onFailedTame();
    /*25*/ virtual void vehicleLanded(class Vec3 const&, class Vec3 const&);
    /*26*/ virtual void onBounceStarted(class BlockPos const&, class Block const&);
    /*27*/ virtual void handleEntityEvent(int /*enum enum ActorEvent*/, int);
    /*28*/ virtual float getPickRadius();
    /*29*/ virtual void awardKillScore(class Actor&, int);
    /*30*/ virtual class HashedString const& queryEntityRenderer() const;
    /*31*/ virtual struct ActorUniqueID getSourceUniqueID() const;
    /*32*/ virtual int getPortalWaitTime() const;
    /*33*/ virtual bool canChangeDimensions() const;
    /*34*/ virtual void __unk_vfn_12();
    /*35*/ virtual struct ActorUniqueID getControllingPlayer() const;
    /*36*/ virtual bool canPickupItem(class ItemStack const&) const;
    /*37*/ virtual bool canBePulledIntoVehicle() const;
    /*38*/ virtual void __unk_vfn_13();
    /*39*/ virtual bool canSynchronizeNewEntity() const;
    /*40*/ virtual void __unk_vfn_14();
    /*41*/ virtual void __unk_vfn_15();
    /*42*/ virtual bool isWorldBuilder() const;
    /*43*/ virtual void __unk_vfn_16();
    /*44*/ virtual bool isAdventure() const;
    /*45*/ virtual bool canDestroyBlock(class Block const&) const;
    /*46*/ virtual void setAuxValue(int);
    /*47*/ virtual void stopSpinAttack();
    /*48*/ virtual void __unk_vfn_17();
    /*49*/ virtual void __unk_vfn_18();
    /*50*/ virtual void updateEntitySpecificMolangVariables(class RenderParams&);
    /*51*/ virtual void __unk_vfn_19();
    /*52*/ virtual void readAdditionalSaveData(class CompoundTag const&, class DataLoadHelper&);
    /*53*/ virtual void addAdditionalSaveData(class CompoundTag&);
    /*54*/ virtual void __unk_vfn_20();
    /*55*/ virtual void _onSizeUpdated();
    /*56*/ virtual void __unk_vfn_21();
    /*57*/ virtual void spawnAnim();
    /*58*/ virtual void aiStep();
    /*59*/ virtual bool checkSpawnRules(bool);
    /*60*/ virtual float getItemUseStartupProgress() const;
    /*61*/ virtual float getItemUseIntervalProgress() const;
    /*62*/ virtual void __unk_vfn_22();
    /*63*/ virtual bool isAlliedTo(class Mob*);
    /*64*/ virtual void __unk_vfn_23();
    /*65*/ virtual void sendArmorDamage(class std::bitset<4> const&);
    /*66*/ virtual int getDamageAfterMagicAbsorb(class ActorDamageSource const&, int);
    /*67*/ virtual void onBorn(class Actor&, class Actor&);
    /*68*/ virtual int getAttackTime();
    /*69*/ virtual void __unk_vfn_24();
    /*70*/ virtual void _serverAiMobStep();
    /*71*/ virtual void __unk_vfn_25();
    MCAPI Witch(class ActorDefinitionGroup*, struct ActorDefinitionIdentifier const&, class OwnerPtrT<struct EntityRefTraits> const&);

protected:

private:
    MCAPI static class std::shared_ptr<class AttributeModifier> SPEED_MODIFIER_DRINKING;
    MCAPI static class mce::UUID const SPEED_MODIFIER_DRINKING_UUID;

};