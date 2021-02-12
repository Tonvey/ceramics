#pragma once
#include "../CeramicsMacro.h"
CERAMICS_NAMESPACE_BEGIN
class IDataBuffer{
public:
    virtual ~IDataBuffer(){};
    virtual void *data()const = 0 ;
    virtual size_t size()const = 0 ;
};
CERAMICS_NAMESPACE_END
