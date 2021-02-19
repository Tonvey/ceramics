#pragma once
#include <algorithm>
#include <functional>
#include <memory>
#include <vector>
#include "../CeramicsType.h"
#include "TEvent.hpp"
CERAMICS_NAMESPACE_BEGIN
class Object3D : public MultipleInheritableEnableSharedFromThis {
    CERAMICS_FORCE_CLASS_SHARED_CREATE_DECLARE(Object3D)
public:
    typedef Object3D type;
    typedef Object3D &type_ref;
    // typedef SharedPtr<type> shared_ptr_t;
    // typedef WeakPtr<type> weak_ptr_t;
    typedef std::vector<shared_ptr_t> children_t;
    typedef std::function<void()> callback_type;

    virtual ~Object3D(){};
    static Vector3 DefaultUp;
    static bool DefaultMatrixAutoUpdate;

protected:
    Object3D();

//     template <class... T>
//     static shared_ptr_t create(T... args) {
//         return shared_ptr_t(new type(args...));
//     }

// protected:
//     shared_ptr_t getSharedPtr();

public:
    TEvent<> addEvent;
    TEvent<> removeEvent;
    String name;
    weak_ptr_t parent;
    children_t children;

    Vector3 position;
    Euler rotation;
    Quaternion quaternion;
    Vector3 scale;
    Vector3 up = DefaultUp;

    Matrix4 matrix;
    Matrix4 matrixWorld;

    bool matrixAutoUpdate = DefaultMatrixAutoUpdate;
    bool matrixWorldNeedsUpdate = false;

    // this->layers = new Layers();
    bool visible = true;

    bool castShadow = false;
    bool receiveShadow = false;

    bool frustumCulled = true;
    int renderOrder = 0;

    void init();
    callback_type onBeforeRender;
    callback_type onAfterRender;

public:
    void applyMatrix4(const Matrix4 &matrix);

    type_ref applyQuaternion(const Quaternion &q);

    void setRotationFromAxisAngle(const Vector3 &axis, number_t angle);

    void setRotationFromEuler(const Euler &euler);

    void setRotationFromMatrix(const Matrix4 &m);

    void setRotationFromQuaternion(const Quaternion &q);

    type_ref rotateOnAxis(const Vector3 &axis, number_t angle);

    type_ref rotateOnWorldAxis(const Vector3 &axis, number_t angle);

    type_ref rotateX(number_t angle);

    type_ref rotateY(number_t angle);

    type_ref rotateZ(number_t angle);

    type_ref translateOnAxis(const Vector3 &axis, number_t distance);

    type_ref translateX(number_t distance);

    type_ref translateY(number_t distance);

    type_ref translateZ(number_t distance);

    Vector3 &localToWorld(Vector3 &vector);

    Vector3 &worldToLocal(Vector3 &vector);

    virtual void lookAt(const Vector3 &target);

    virtual void lookAt(number_t x, number_t y, number_t z);

    // TODO 改为 不定参数模板?
    type_ref add(shared_ptr_t &object);

    type_ref remove(shared_ptr_t &object);

    type_ref clear();

    type_ref attach(shared_ptr_t &object);

    // getObjectById: function ( id ) {

    // 	return this->getObjectByProperty( 'id', id );

    // },

    // getObjectByName: function ( name ) {

    // 	return this->getObjectByProperty( 'name', name );

    // },

    // getObjectByProperty: function ( name, value ) {

    // 	if ( this[ name ] === value ) return this;

    // 	for ( let i = 0, l = this->children.length; i < l; i ++ ) {

    // 		const child = this->children[ i ];
    // 		const object = child.getObjectByProperty( name, value );

    // 		if ( object !== undefined ) {

    // 			return object;

    // 		}

    // 	}

    // 	return undefined;

    // },

    Vector3 &getWorldPosition(Vector3 &target);

    Quaternion &getWorldQuaternion(Quaternion &target);

    Vector3 &getWorldScale(Vector3 &target);

    Vector3 &getWorldDirection(Vector3 &target);

    virtual void raycast();

    virtual void traverse(std::function<void(shared_ptr_t)> &callback);

    virtual void traverseVisible(std::function<void(shared_ptr_t)> &callback);

    virtual void traverseAncestors(std::function<void(shared_ptr_t)> &callback);

    virtual void updateMatrix();

    virtual void updateMatrixWorld(bool force);

    virtual void updateWorldMatrix(bool updateParents, bool updateChildren);
};
Vector3 Object3D::DefaultUp(0, 1, 0);
bool Object3D::DefaultMatrixAutoUpdate = true;
CERAMICS_NAMESPACE_END
