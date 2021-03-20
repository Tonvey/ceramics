#include "AutoReleasePool.h"
CERAMICS_NAMESPACE_BEGIN
AutoReleasePool::AutoReleasePool()
{
    mManagedObjectArray.reserve(150);
    PoolManager::getInstance()->push(this);
}
AutoReleasePool::~AutoReleasePool()
{
    clear();
    PoolManager::getInstance()->pop();
}

void AutoReleasePool::addObject(Ref *object)
{
    mManagedObjectArray.push_back(object);
}
void AutoReleasePool::clear()
{
    std::vector<Ref*> releasings;
    releasings.swap(mManagedObjectArray);
    for (const auto &obj : releasings)
    {
        obj->release();
    }
}
bool AutoReleasePool::contains(Ref* object) const
{
    for (const auto& obj : mManagedObjectArray)
    {
        if (obj == object)
            return true;
    }
    return false;
}

PoolManager* PoolManager::getInstance()
{
    if (smSingleInstance == nullptr)
    {
        smSingleInstance = new (std::nothrow) PoolManager();
        new AutoReleasePool();
    }
    return smSingleInstance;
}
void PoolManager::destroyInstance()
{
    delete smSingleInstance;
    smSingleInstance = nullptr;
}
AutoReleasePool *PoolManager::getCurrentPool() const
{
    return mReleasePoolStack.back();
}
bool PoolManager::isObjectInPools(Ref* obj) const
{
    for (const auto& pool : mReleasePoolStack)
    {
        if (pool->contains(obj))
            return true;
    }
    return false;
}
PoolManager::PoolManager()
{
    mReleasePoolStack.reserve(10);
}
PoolManager::~PoolManager()
{
    while (!mReleasePoolStack.empty())
    {
        AutoReleasePool* pool = mReleasePoolStack.back();
        
        delete pool;
    }
}
void PoolManager::push(AutoReleasePool *pool)
{
    mReleasePoolStack.push_back(pool);
}
void PoolManager::pop()
{
    assert(!mReleasePoolStack.empty());
    mReleasePoolStack.pop_back();
}
PoolManager *PoolManager::smSingleInstance = nullptr;
CERAMICS_NAMESPACE_END
