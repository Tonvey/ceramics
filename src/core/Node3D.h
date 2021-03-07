#pragma once
#include <algorithm>
#include <functional>
#include <memory>
#include <vector>
#include "../CeramicsType.h"
#include "Object.h"
#include "TEvent.hpp"
CERAMICS_NAMESPACE_BEGIN
class Node3D : public Object
{
public:
    typedef Node3D type;
    typedef std::vector<type*> children_t;

    Node3D();
    virtual ~Node3D();
    static Vector3 DefaultUp;
    static bool DefaultMatrixAutoUpdate;

public:
    TEvent<> addEvent;
    TEvent<> removeEvent;
    // callback_type onBeforeRender;
    // callback_type onAfterRender;

    Vector3 getPosition()const{return mPosition;};
    Euler getEuler()const{return mEuler;};
    Quaternion getQuaternion()const{return mQuaternion;};
    Vector3 getScale()const{return mScale;};
    Vector3 getUp()const{return mUp;};
    type& setPosition(const Vector3 &position);
    type& setEuler(const Euler &euler);
    type& setQuaternion(const Quaternion &quaternion);
    type& setScale(const Vector3 &scale);
    type& setUp(const Vector3 &up);

    bool visible = true;
    bool castShadow = false;
    bool receiveShadow = false;
    bool frustumCulled = true;
    int renderOrder = 0;
    void init();

public:

    Matrix4 getMatrixLocal();

    Matrix4 getMatrixWorld();

    void applyMatrix4(const Matrix4 &matrix);

    type& applyQuaternion(const Quaternion &q);

    type& translateOnAxis(const Vector3 &axis, Real distance);

    type& translate(const Vector3 &translate);

    Vector3 &localToWorld(Vector3 &vector);

    Vector3 &worldToLocal(Vector3 &vector);

    virtual void lookAt(const Vector3 &target);

    // TODO 改为 不定参数模板?
    type& add(type *object);

    type& remove(type *object);

    type& clear();

    type& attach(type *object);

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

    Vector3 &getWorldDirection();

    virtual void raycast();

    virtual void traverse(std::function<void(type*)> &callback);

    virtual void traverseVisible(std::function<void(type*)> &callback);

    virtual void traverseAncestors(std::function<void(type*)> &callback);

    virtual void updateMatrixLocal();

    virtual void updateMatrixWorld();

    void setParent(type *parent);
    // virtual void updateMatrixWorld(bool force);

    // virtual void updateWorldMatrix(bool updateParents, bool updateChildren);

protected:
    void setMatrixWorldNeedUpdate();
    Matrix4 mMatrixLocal;
    Matrix4 mMatrixWorld;
    Vector3 mPosition;
    Euler mEuler;
    Quaternion mQuaternion;
    Vector3 mScale = Vector3(1,1,1);
    Vector3 mUp = DefaultUp;
    type *mParent = nullptr;
    children_t mChildren;
    bool mMatrixLocalNeedUpdate = false;
    bool mMatrixWorldNeedUpdate = false;

};
// bool Node3D::DefaultMatrixAutoUpdate = true;
CERAMICS_NAMESPACE_END
