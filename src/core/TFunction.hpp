#pragma once
#include "Ref.h"
#include <functional>
CERAMICS_NAMESPACE_BEGIN
template<class T>
class TFunction : public std::function<T> , public Ref
{
public:
    typedef TFunction<T> type;
    TFunction(T fn):std::function<T>(fn){};
    TFunction(const type &other) = delete;
    TFunction(type &&other) = delete;
    type &operator=(const type &other) = delete;
    type &operator=(type &&other) = delete;
};
CERAMICS_NAMESPACE_END
