#pragma once
#include "../CeramicsMacro.h"
CERAMICS_NAMESPACE_BEGIN
class Ref {
public:
    Ref();
    virtual ~Ref();
    void release();
    void retain();
    int refCount()const{return mRefCount;};
private:
    int mRefCount;
};
CERAMICS_NAMESPACE_END
