#pragma once
#include "Ref.h"
CERAMICS_NAMESPACE_BEGIN
template<class T>
class RefPtr {
public:
    typedef RefPtr<T> type;
    RefPtr(T *ptr = nullptr)
        :mPtr(ptr)
    {
    }
        
    RefPtr(const type &other);
    ~RefPtr()
    {
        if(nullptr!=mPtr)
        {
            mPtr->release();
        }
    }
    Ref *get();
    RefPtr &operator=(const type &other);
    RefPtr &operator=(type &&other);
 private:
    T *mPtr;
};
CERAMICS_NAMESPACE_END
