#pragma once
#include "../CeramicsMacro.h"
#include "Ref.h"
#include <vector>
CERAMICS_NAMESPACE_BEGIN
// Copy from cocos2d-x
class CERAMICS_EXPORT AutoReleasePool
{
public:
    AutoReleasePool();
    ~AutoReleasePool();

    void addObject(Ref *object);
    void clear();
    bool contains(Ref* object) const;

private:
    std::vector<Ref*> mManagedObjectArray;
};

class CERAMICS_EXPORT PoolManager
{
public:
    AutoReleasePool *getCurrentPool() const;
    bool isObjectInPools(Ref* obj) const;
    static PoolManager* getInstance();
    static void destroyInstance();
    friend class AutoReleasePool;
private:
    PoolManager();
    ~PoolManager();
    void push(AutoReleasePool *pool);
    void pop();
    static PoolManager *smSingleInstance;
    std::vector<AutoReleasePool*> mReleasePoolStack;
};
CERAMICS_NAMESPACE_END
