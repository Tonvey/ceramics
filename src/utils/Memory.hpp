#pragma once
#include <memory>

#include "../ThreeTypes.h"
#define THREE_FORCE_CLASS_SHARED_CREATE_DECLARE(className)       \
public:                                                          \
    typedef SharedPtr<className> shared_ptr_t;                   \
    typedef WeakPtr<className> weak_ptr_t;                       \
    template <class... T>                                        \
    static shared_ptr_t create(T... args) {                      \
        return shared_ptr_t(new className(args...));             \
    }                                                            \
                                                                 \
protected:                                                       \
    void getSharedPtr(shared_ptr_t& ptr) {                       \
        ptr = DynamicPointerCast<className>(shared_from_this()); \
    }

THREE_NAMESPACE_BEGIN
// Wrapper for shared_ptr
// TODO : Use single thread shared_ptr improve perfomance
template <class... T>
using SharedPtr = std::shared_ptr<T...>;
template <class... T>
using WeakPtr = std::weak_ptr<T...>;
template <class... T>
using EnableSharedFromThis = std::enable_shared_from_this<T...>;
template <class T, class U>
SharedPtr<T> StaticPointerCast(const SharedPtr<U>& r) {
    return std::static_pointer_cast<T>(r);
}
template <class T, class U>
SharedPtr<T> DynamicPointerCast(const SharedPtr<U>& r) {
    return std::dynamic_pointer_cast<T>(r);
}
template <class T, class U>
SharedPtr<T> ConstPointerCast(const SharedPtr<U>& r) {
    return std::const_pointer_cast<T>(r);
}
class MultipleInheritableEnableSharedFromThis
    : protected EnableSharedFromThis<MultipleInheritableEnableSharedFromThis> {
public:
    virtual ~MultipleInheritableEnableSharedFromThis() {}
};

THREE_NAMESPACE_END