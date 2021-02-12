#pragma once
#include "../ThreeMacros.h"
THREE_NAMESPACE_BEGIN
class IDataBuffer{
public:
    virtual ~IDataBuffer(){};
    virtual void *data()const = 0 ;
    virtual size_t size()const = 0 ;
};
THREE_NAMESPACE_END
