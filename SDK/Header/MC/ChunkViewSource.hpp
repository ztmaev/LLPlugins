// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "ChunkSource.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class ChunkViewSource : public ChunkSource {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_CHUNKVIEWSOURCE
public:
    class ChunkViewSource& operator=(class ChunkViewSource const&) = delete;
    ChunkViewSource() = delete;
#endif

public:
    /*0*/ virtual ~ChunkViewSource();
    /*1*/ virtual class std::shared_ptr<class LevelChunk> getExistingChunk(class ChunkPos const&);
    /*2*/ virtual class std::shared_ptr<class LevelChunk> getRandomChunk(class Random&);
    /*3*/ virtual class std::shared_ptr<class LevelChunk> createNewChunk(class ChunkPos const&, enum ChunkSource::LoadMode, bool);
    /*4*/ virtual bool postProcess(class ChunkViewSource&);
    /*5*/ virtual void checkAndReplaceChunk(class ChunkViewSource&, class LevelChunk&);
    /*6*/ virtual void acquireDiscarded(class std::unique_ptr<class LevelChunk, struct LevelChunkFinalDeleter>);
    /*7*/ virtual bool isWithinWorldLimit(class ChunkPos const&) const;
    /*8*/ virtual class std::unordered_map<class ChunkPos, class std::weak_ptr<class LevelChunk>, struct std::hash<class ChunkPos>, struct std::equal_to<class ChunkPos>, class std::allocator<struct std::pair<class ChunkPos const, class std::weak_ptr<class LevelChunk> > > > const* getChunkMap();
    /*9*/ virtual void clearDeletedEntities();
    /*10*/ virtual bool canCreateViews() const;
    /*
    inline  ~ChunkViewSource(){
         (ChunkViewSource::*rv)();
        *((void**)&rv) = dlsym("??1ChunkViewSource@@UEAA@XZ");
        return (this->*rv)();
    }
    */
    MCAPI ChunkViewSource(class ChunkSource&, class LevelChunkGridAreaElement<class std::weak_ptr<class LevelChunk> >&, struct Bounds const&);
    MCAPI ChunkViewSource(class ChunkSource&, enum ChunkSource::LoadMode);
    MCAPI ChunkViewSource(class ChunkViewSource const&);
    MCAPI void clear();
    MCAPI void clearEntryAtChunkPos(class ChunkPos const&);
    MCAPI std::vector<class LevelChunkBlockActorAccessToken> enableBlockEntityAccess();
    MCAPI class GridArea<class std::shared_ptr<class LevelChunk> >& getArea();
    MCAPI void move(struct Bounds const&, bool, class std::function<void (class buffer_span_mut<class std::shared_ptr<class LevelChunk> >, class buffer_span<unsigned int>)>);
    MCAPI void move(class BlockPos const&, class BlockPos const&, bool, class std::function<void (class buffer_span_mut<class std::shared_ptr<class LevelChunk> >, class buffer_span<unsigned int>)>);
    MCAPI void move(class BlockPos const&, int, bool, class std::function<void (class buffer_span_mut<class std::shared_ptr<class LevelChunk> >, class buffer_span<unsigned int>)>);
    MCAPI void rebuildSpecificArea(struct Bounds const&, bool, class std::function<void (class buffer_span_mut<class std::shared_ptr<class LevelChunk> >, class buffer_span<unsigned int>)>);

protected:

private:

};