#include "Ref.h"
#include <cassert>
CERAMICS_NAMESPACE_BEGIN
Ref::Ref()
    :mRefCount(0)
{
}
Ref::~Ref()
{
    assert(mRefCount==0);
}
void Ref::release()
{
    assert(mRefCount>0);
    if(--mRefCount==0)
    {
        delete this;
    }
}
void Ref::retain()
{
    ++mRefCount;
}
CERAMICS_NAMESPACE_END
