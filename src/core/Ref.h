#pragma once
#include "../CeramicsMacro.h"
#include <cassert>
CERAMICS_NAMESPACE_BEGIN
class CERAMICS_EXPORT Ref {
public:
    Ref();
    virtual ~Ref();
    void release();
    void retain();
    int refCount()const{return mRefCount;};
    Ref *autoRelease();
private:
    int mRefCount;
};

template<class T>
class RefPtr {
public:
    typedef RefPtr<T> type;
    RefPtr(const type &other) = delete;
    RefPtr(type &&other) = delete;
    void reset(T *ptr = nullptr)
    {
        if(ptr!=mPtr)
        {
            if(mPtr!=nullptr)
            {
                mPtr->release();
                mPtr=nullptr;
            }
            if(ptr!=nullptr)
            {
                mPtr=ptr;
                mPtr->retain();
            }
        }
    }
    operator bool() const
    {
        return mPtr!=nullptr;
    }
    T &operator*() const
    {
        return *mPtr;
    }
    T *operator->() const
    {
        return mPtr;
    }
    T *get(){return mPtr;};
protected:
    RefPtr(T *ptr = nullptr)
        :mPtr(ptr)
    {
        mPtr->retain();
    }
    virtual ~RefPtr()
    {
        reset();
    }
protected:
    T *mPtr;
};
template<class T>
class RefUniquePtr : public RefPtr<T> {
public:
    typedef RefUniquePtr<T> type;
    using RefPtr<T>::operator bool;
    using RefPtr<T>::operator*;
    using RefPtr<T>::operator->;
    RefUniquePtr(T *ptr = nullptr)
        :RefPtr<T>(ptr)
    {
    }
    RefUniquePtr(type &&other)
    {
        assert(other.mPtr!=this->mPtr);
        reset(other.mPtr);
        other.reset();
    }
    RefUniquePtr(const type &other) = delete;
    RefUniquePtr &operator=(const type &other) = delete;
    RefUniquePtr &operator=(type &&other) = delete;
};

template<class T>
class RefSharedPtr : public RefPtr<T> {
public:
    typedef RefUniquePtr<T> type;
    using RefPtr<T>::operator bool;
    using RefPtr<T>::operator*;
    using RefPtr<T>::operator->;
    RefSharedPtr(T *ptr = nullptr)
        :RefPtr<T>(ptr)
    {
    }
    RefSharedPtr(const type &other)
    {
        reset(other.mPtr);
    }
    RefSharedPtr(type &&other)
    {
        reset(other.mPtr);
        other.reset();
    }
    RefSharedPtr &operator=(const type &other)
    {
        reset(other.mPtr);
    }
    RefSharedPtr &operator=(type &&other)
    {
        reset(other.mPtr);
        other.reset();
    }
    bool operator == (const type &other) const { return this->mPtr == other.mPtr; }
    bool operator != (const type &other) const { return this->mPtr != other.mPtr; }
};
CERAMICS_NAMESPACE_END
