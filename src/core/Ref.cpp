#include "Ref.h"
#include <cassert>
CERAMICS_NAMESPACE_BEGIN
Ref::Ref()
    :mRefCount(1)
{
}
Ref::~Ref()
{
}
void Ref::release()
{
    assert(mRefCount>0);
    --mRefCount;
    if(mRefCount==0)
    {
        delete this;
    }
}
void Ref::retain()
{
    assert(mRefCount>0);
    ++mRefCount;
}
CERAMICS_NAMESPACE_END
