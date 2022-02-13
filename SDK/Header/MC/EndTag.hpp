// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "Tag.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class EndTag : public Tag {

#define AFTER_EXTRA
// Add Member There
public:
    LIAPI nullptr_t value();
    LIAPI static std::unique_ptr<EndTag> create();
    LIAPI bool set();
    LIAPI nullptr_t get();

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_ENDTAG
public:
    class EndTag& operator=(class EndTag const&) = delete;
    EndTag(class EndTag const&) = delete;
    EndTag() = delete;
#endif

public:
    /*0*/ virtual ~EndTag();
    /*1*/ virtual void deleteChildren();
    /*2*/ virtual void write(class IDataOutput&) const;
    /*3*/ virtual void load(class IDataInput&);
    /*4*/ virtual std::string toString() const;
    /*5*/ virtual enum Tag::Type getId() const;
    /*6*/ virtual bool equals(class Tag const&) const;
    /*9*/ virtual std::unique_ptr<class Tag> copy() const;
    /*10*/ virtual unsigned __int64 hash() const;

protected:

private:

};