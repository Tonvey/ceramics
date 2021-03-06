#pragma once
#include "../CeramicsMacro.h"
#include "Ref.h"
#include <type_traits>
#include <cassert>
CERAMICS_NAMESPACE_BEGIN
class Object : public Ref
{
public:
    Object();
    virtual ~Object();
};
template<class T,class ...Args>
static T *CreateObject(Args ...args)
{
    static_assert(std::is_base_of<Object,T>::value,"Error: Not inherit from Object.");
    auto ret = new T(args...);
    ret->retain();
    return ret;
}
CERAMICS_NAMESPACE_END
