#pragma once
#include "../CeramicsMacro.h"
#include <list>
#include <functional>
#include <algorithm>
#include <memory>
CERAMICS_NAMESPACE_BEGIN
template<class ...T>
class TEvent {
public:
    typedef std::function<void (T ...args)> listener_t;
    typedef std::shared_ptr<listener_t> pListener_t;
    void dispatch(T ...args){
        for(auto i: mListenerList){
            (*i)(args...);
        }
    }
    TEvent &operator+=(listener_t &listener){
        auto it = std::find(mListenerList.begin(),mListenerList.end(),listener);
        if(it==mListenerList.end()){
            mListenerList.push_back(listener);
        }
        return *this;
    }
    TEvent &operator-=(listener_t &listener){
        auto it = std::find(mListenerList.begin(),mListenerList.end(),listener);
        if(it!=mListenerList.end()){
            mListenerList.erase(it);
        }
        return *this;
    }
    TEvent &clear(){
        mListenerList.clear();
        return *this;
    }
private:
    std::list<pListener_t> mListenerList;
};
CERAMICS_NAMESPACE_END
