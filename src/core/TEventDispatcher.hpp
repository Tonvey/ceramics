#pragma once
#include "../CeramicsMacro.h"
#include <list>
#include <functional>
#include "TFunction.hpp"
CERAMICS_NAMESPACE_BEGIN
template<class ...T>
class TEventDispatcher
{
public:
    //typedef std::function<void (T ...args)> listener_t;
    //typedef std::shared_ptr<listener_t> pListener_t;
    typedef TFunction<void (T ...args)> listener_t;
    typedef listener_t* pListener_t;
    TEventDispatcher &operator+=(pListener_t listener)
    {
        auto it = std::find(mListenerList.begin(),mListenerList.end(),listener);
        if(it==mListenerList.end())
        {
            listener->retain();
            mListenerList.push_back(listener);
        }
        return *this;
    }
    TEventDispatcher &operator-=(listener_t &listener)
    {
        auto it = std::find(mListenerList.begin(),mListenerList.end(),listener);
        if(it!=mListenerList.end())
        {
            mListenerList.erase(it);
            listener->release();
        }
        return *this;
    }
    TEventDispatcher &clear()
    {
        for(auto &i : mListenerList)
        {
            i->release();
        }
        mListenerList.clear();
        return *this;
    }
    void operator()(T ...args)
    {
        invoke(args...);
    }
    void invoke(T ...args)
    {
        for(auto &i: mListenerList)
        {
            (*i)(args...);
        }
    }
private:
    std::list<pListener_t> mListenerList;
};
CERAMICS_NAMESPACE_END
