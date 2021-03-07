#include "Node3D.h"
#define VEC3_AXIS_X (Vector3(1, 0, 0))
#define VEC3_AXIS_Y (Vector3(0, 1, 0))
#define VEC3_AXIS_Z (Vector3(0, 0, 1))
CERAMICS_NAMESPACE_BEGIN
Vector3 Node3D::DefaultUp(0, 1, 0);
Node3D::Node3D()
{
    this->mUp = Node3D::DefaultUp;
    init();
}
Node3D::~Node3D()
{
    clear();
    // TODO remove from parent
    // if(mParent!=nullptr)
    // {
    //     mParent->remove(this);
    // }
}
void Node3D::init()
{
    // rotation._onChange(
    //     [this]() { this->mQuaternion.setFromEuler(this->rotation, false); });
    // quaternion._onChange([this]() {
    //     this->rotation.setFromQuaternion(this->mQuaternion, XYZ, false);
    // });
    // TODO
    // this->userData = {};
}

Node3D::type& Node3D::setPosition(const Vector3 &position)
{
    mPosition = position;
    mMatrixLocalNeedUpdate = true;
    return *this;
}
Node3D::type& Node3D::setEuler(const Euler &euler)
{
    mEuler = euler;
    mQuaternion.setFromEuler(mEuler);
    mMatrixLocalNeedUpdate = true;
    return *this;
}
Node3D::type& Node3D::setQuaternion(const Quaternion &quaternion)
{
    mQuaternion = quaternion;
    mEuler.setFromQuaternion(mQuaternion,mEuler.order);
    mMatrixLocalNeedUpdate = true;
    return *this;
}
Node3D::type& Node3D::setScale(const Vector3 &scale)
{
    mScale = scale;
    mMatrixLocalNeedUpdate = true;
    return *this;
}
Node3D::type& Node3D::setUp(const Vector3 &up)
{
    mUp = up;
    mMatrixLocalNeedUpdate = true;
    return *this;
}
Matrix4 Node3D::getMatrixLocal()
{
    updateMatrixLocal();
    return mMatrixLocal;
}

Matrix4 Node3D::getMatrixWorld()
{
    updateMatrixWorld();
    return mMatrixWorld;
}

void Node3D::applyMatrix4(const Matrix4 &matrix)
{
    this->updateMatrixLocal();
    this->mMatrixLocal = matrix * this->mMatrixLocal;
    this->mMatrixLocal.decompose(this->mPosition, this->mQuaternion, this->mScale);
}

Node3D::type& Node3D::applyQuaternion(const Quaternion &q)
{
    this->mQuaternion.premultiply(q);
    this->mEuler.setFromQuaternion(mQuaternion);
    mMatrixLocalNeedUpdate = true;
    return *this;
}

Node3D::type& Node3D::translateOnAxis(const Vector3 &axis, Real distance)
{
    // translate object by distance along axis in object space
    // axis is assumed to be normalized
    Vector3 v;
    v = axis;
    v.applyQuaternion(this->mQuaternion);

    this->mPosition.add(v.multiplyScalar(distance));
    mMatrixLocalNeedUpdate = true;

    return *this;
}

Node3D::type& Node3D::translate(const Vector3 &translate)
{
    this->mPosition+=translate;
    mMatrixLocalNeedUpdate = true;
    return *this;
}

Vector3 &Node3D::localToWorld(Vector3 &vector)
{
    return vector.applyMatrix4(this->getMatrixWorld());
}

Vector3 &Node3D::worldToLocal(Vector3 &vector)
{
    Matrix4 m = this->getMatrixWorld().getInverse();
    return vector.applyMatrix4(m);
}

void Node3D::lookAt(const Vector3 &target)
{
    Vector3 position;
    Matrix4 m;
    Quaternion q;

    // this->updateWorldMatrix(true, false);
    this->updateMatrixWorld();

    position.setFromMatrixPosition(this->mMatrixWorld);

    // TODO rewrite in subclass
    // if (this->isCamera || this->isLight) {
        m.lookAt(position, target, this->mUp);

    // } else {
    // m.lookAt(target, position, this->mUp);
    // }

    this->mQuaternion.setFromRotationMatrix(m);

    if (mParent != nullptr)
    {
        m.extractRotation(mParent->mMatrixWorld);
        q.setFromRotationMatrix(m);
        this->mQuaternion.premultiply(q.inverse());
    }
    this->mEuler.setFromQuaternion(mQuaternion);
    mMatrixLocalNeedUpdate = true;
}

void Node3D::setParent(type *parent)
{
    //TODO
    mParent = parent;
}
Node3D::type& Node3D::add(type *object)
{
    if(object != this)
    {
        if (mParent != nullptr)
        {
            mParent->remove(object);
        }

        object->retain();
        object->setParent(this);
        this->mChildren.push_back(object);
        object->addEvent();

        object->setMatrixWorldNeedUpdate();
    }

    return *this;
}

Node3D::type& Node3D::remove(type *object)
{
    auto it = std::find(mChildren.begin(), mChildren.end(), object);

    if (it != mChildren.end())
    {
        mChildren.erase(it);
        object->removeEvent();
        object->setParent(nullptr);
        object->release();
    }

    return *this;
}

Node3D::type& Node3D::clear()
{
    for (auto it = mChildren.begin(); it < mChildren.end();)
    {
        (*it)->removeEvent();
        (*it)->setParent(nullptr);
        (*it)->release();
        it = mChildren.erase(it);
    }
    return *this;
}

Node3D::type& Node3D::attach(type *object)
{
    // adds object as a child of this, while maintaining the object's world
    // transform

    Matrix4 m;

    // this->updateWorldMatrix(true, false);
    this->updateMatrixWorld();

    m = this->mMatrixWorld.getInverse();

    if (mParent != nullptr)
    {
        // originParent->updateWorldMatrix(true, false);
        //TODO
        m *= mParent->mMatrixWorld;
    }

    object->applyMatrix4(m);

    // object->updateWorldMatrix(false, false);

    this->add(object);

    return *this;
}

Vector3 &Node3D::getWorldPosition(Vector3 &target)
{
    // if ( target === undefined ) {

    // 	console.warn( 'THREE.Node3D: .getWorldPosition() target is now
    // required' ); 	target = new Vector3();

    // }

    // this->updateWorldMatrix(true, false);

    return target.setFromMatrixPosition(this->getMatrixWorld());
}

Quaternion &Node3D::getWorldQuaternion(Quaternion &target)
{
    // if ( target === undefined ) {

    // 	console.warn( 'THREE.Node3D: .getWorldQuaternion() target is now
    // required' ); 	target = new Quaternion();

    // }

    Vector3 _position, _scale;

    // this->updateWorldMatrix(true, false);

    this->getMatrixWorld().decompose(_position, target, _scale);

    return target;
}

Vector3 &Node3D::getWorldScale(Vector3 &target)
{
    // if ( target === undefined ) {

    // 	console.warn( 'THREE.Node3D: .getWorldScale() target is now required'
    // ); 	target = new Vector3();

    // }

    // this->updateWorldMatrix(true, false);
    // this->updateMatrixWorld();

    Vector3 _position;
    Quaternion _quaternion;
    this->getMatrixWorld().decompose(_position, _quaternion, target);

    return target;
}

Vector3 &Node3D::getWorldDirection()
{
    Vector3 ret;
    // if ( target === undefined ) {

    // 	console.warn( 'THREE.Node3D: .getWorldDirection() target is now
    // required' ); 	target = new Vector3();

    // }

    // this->updateWorldMatrix(true, false);
    this->updateMatrixWorld();

    auto &e = this->mMatrixWorld.elements;

    return ret.set(e[2], e[6], e[10]).normalize();
}

void Node3D::raycast() {}

void Node3D::traverse(std::function<void(type*)> &callback)
{
    callback(this);
    for (auto &i : mChildren)
    {
        i->traverse(callback);
    }
}

void Node3D::traverseVisible(std::function<void(type*)> &callback)
{
    if (this->visible == false) return;

    callback(this);

    for (auto &i : mChildren)
    {
        i->traverseVisible(callback);
    }
}

void Node3D::traverseAncestors(
                               std::function<void(type*)> &callback)
{

    if (mParent != nullptr)
    {
        callback(mParent);

        mParent->traverseAncestors(callback);
    }
}
void Node3D::updateMatrixLocal()
{
    if(!mMatrixLocalNeedUpdate)
        return;

    this->mMatrixLocal.compose(this->mPosition, this->mQuaternion, this->mScale);

    this->setMatrixWorldNeedUpdate();
}

void Node3D::setMatrixWorldNeedUpdate()
{
    mMatrixWorldNeedUpdate = true;
    for (auto &i : mChildren)
    {
        i->setMatrixWorldNeedUpdate();
    }
}
void Node3D::updateMatrixWorld()
{
    this->updateMatrixLocal();

    if (mParent == nullptr)
    {
        this->mMatrixWorld = this->mMatrixLocal;
    }
    else
    {
        mParent->updateMatrixWorld();
        if (this->mMatrixWorldNeedUpdate)
        {
            this->mMatrixWorld = mParent->mMatrixWorld* this->mMatrixLocal;
        }
    }
    this->mMatrixWorldNeedUpdate = false;


    // update children
    // for (auto &i : mChildren)
    // {
    //     i->updateMatrixWorld(force);
    // }
}

// void Node3D::updateWorldMatrix(bool updateParents, bool updateChildren)
// {
//     auto originParent = this->mParent.lock();
//     if (updateParents && originParent != nullptr)
//     {
//         originParent->updateWorldMatrix(true, false);
//     }

//     this->updateMatrixLocal();

//     if (originParent == nullptr)
//     {
//         this->mMatrixWorld = this->mMatrixLocal;

//     }
//     else
//     {
//         this->mMatrixWorld.multiplyMatrices(originParent->mMatrixWorld,
//                                            this->mMatrixLocal);
//     }

//     // update children

//     if (updateChildren)
//     {
//         for (auto &i : mChildren)
//         {
//             i->updateWorldMatrix(false, true);
//         }
//     }
// }

CERAMICS_NAMESPACE_END
