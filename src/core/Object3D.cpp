#include "Object3D.h"
#define VEC3_AXIS_X (Vector3(1, 0, 0))
#define VEC3_AXIS_Y (Vector3(0, 1, 0))
#define VEC3_AXIS_Z (Vector3(0, 0, 1))
CERAMICS_NAMESPACE_BEGIN
Object3D::Object3D() {
    this->up = Object3D::DefaultUp;
    init();
}
void Object3D::init() {
    rotation._onChange(
        [this]() { this->quaternion.setFromEuler(this->rotation, false); });
    quaternion._onChange([this]() {
        this->rotation.setFromQuaternion(this->quaternion, XYZ, false);
    });
    // TODO
    // this->userData = {};
}

void Object3D::applyMatrix4(const Matrix4 &matrix) {
    if (this->matrixAutoUpdate) this->updateMatrix();

    this->matrix.premultiply(matrix);
    this->matrix.decompose(this->position, this->quaternion, this->scale);
}

Object3D::type_ref Object3D::applyQuaternion(const Quaternion &q) {
    this->quaternion.premultiply(q);

    return *this;
}

void Object3D::setRotationFromAxisAngle(const Vector3 &axis, number_t angle) {
    // assumes axis is normalized

    this->quaternion.setFromAxisAngle(axis, angle);
}

void Object3D::setRotationFromEuler(const Euler &euler) {
    this->quaternion.setFromEuler(euler, true);
}

void Object3D::setRotationFromMatrix(const Matrix4 &m) {
    // assumes the upper 3x3 of m is a pure rotation matrix (i.e, unscaled)

    this->quaternion.setFromRotationMatrix(m);
}

void Object3D::setRotationFromQuaternion(const Quaternion &q) {
    // assumes q is normalized

    this->quaternion = q;
}

Object3D::type_ref Object3D::rotateOnAxis(const Vector3 &axis, number_t angle) {
    // rotate object on axis in object space
    // axis is assumed to be normalized
    Quaternion _q1;

    _q1.setFromAxisAngle(axis, angle);

    this->quaternion.multiply(_q1);

    return *this;
}

Object3D::type_ref Object3D::rotateOnWorldAxis(const Vector3 &axis,
                                               number_t angle) {
    // rotate object on axis in world space
    // axis is assumed to be normalized
    // method assumes no rotated parent
    Quaternion _q1;

    _q1.setFromAxisAngle(axis, angle);

    this->quaternion.premultiply(_q1);

    return *this;
}

Object3D::type_ref Object3D::rotateX(number_t angle) {
    return this->rotateOnAxis(VEC3_AXIS_X, angle);
}

Object3D::type_ref Object3D::rotateY(number_t angle) {
    return this->rotateOnAxis(VEC3_AXIS_Y, angle);
}

Object3D::type_ref Object3D::rotateZ(number_t angle) {
    return this->rotateOnAxis(VEC3_AXIS_Z, angle);
}

Object3D::type_ref Object3D::translateOnAxis(const Vector3 &axis,
                                             number_t distance) {
    // translate object by distance along axis in object space
    // axis is assumed to be normalized
    Vector3 _v1;

    _v1 = axis;
    _v1.applyQuaternion(this->quaternion);

    this->position.add(_v1.multiplyScalar(distance));

    return *this;
}

Object3D::type_ref Object3D::translateX(number_t distance) {
    return this->translateOnAxis(VEC3_AXIS_X, distance);
}

Object3D::type_ref Object3D::translateY(number_t distance) {
    return this->translateOnAxis(VEC3_AXIS_Y, distance);
}

Object3D::type_ref Object3D::translateZ(number_t distance) {
    return this->translateOnAxis(VEC3_AXIS_Z, distance);
}

Vector3 &Object3D::localToWorld(Vector3 &vector) {
    return vector.applyMatrix4(this->matrixWorld);
}

Vector3 &Object3D::worldToLocal(Vector3 &vector) {
    Matrix4 _m1;
    _m1 = this->matrixWorld.getInverse();
    return vector.applyMatrix4(_m1);
}

void Object3D::lookAt(const Vector3 &target) {
    Vector3 _position;
    Matrix4 _m1;
    Quaternion _q1;

    this->updateWorldMatrix(true, false);

    _position.setFromMatrixPosition(this->matrixWorld);

    // TODO rewrite in subclass
    // if (this->isCamera || this->isLight) {
    //     _m1.lookAt(_position, _target, this->up);

    // } else {
    _m1.lookAt(target, _position, this->up);
    // }

    this->quaternion.setFromRotationMatrix(_m1);

    auto originParent = parent.lock();
    if (originParent != nullptr) {
        _m1.extractRotation(originParent->matrixWorld);
        _q1.setFromRotationMatrix(_m1);
        this->quaternion.premultiply(_q1.inverse());
    }
}

void Object3D::lookAt(number_t x, number_t y, number_t z) {
    // This method does not support objects having non-uniformly-scaled
    // parent(s)

    Vector3 _target;

    _target.set(x, y, z);

    this->lookAt(_target);
}

Object3D::type_ref Object3D::add(shared_ptr_t &object) {
    if (object.get() != this) {
        auto originParent = object->parent.lock();
        if (originParent != nullptr) {
            originParent->remove(object);
        }

        shared_ptr_t ptr;
        this->getSharedPtr(ptr);
        object->parent = ptr;
        this->children.push_back(object);

        object->addEvent.dispatch();
    }

    return *this;
}

Object3D::type_ref Object3D::remove(shared_ptr_t &object) {
    auto it = std::find(children.begin(), children.end(), object);

    if (it != children.end()) {
        object->parent.reset();
        children.erase(it);

        object->removeEvent.dispatch();
    }

    return *this;
}

Object3D::type_ref Object3D::clear() {
    for (auto it = children.begin(); it < children.end();) {
        (*it)->parent.reset();

        it = children.erase(it);

        (*it)->removeEvent.dispatch();
    }

    return *this;
}

Object3D::type_ref Object3D::attach(shared_ptr_t &object) {
    // adds object as a child of this, while maintaining the object's world
    // transform

    Matrix4 _m1;

    this->updateWorldMatrix(true, false);

    _m1 = this->matrixWorld.getInverse();

    auto originParent = object->parent.lock();
    if (originParent != nullptr) {
        originParent->updateWorldMatrix(true, false);

        _m1.multiply(originParent->matrixWorld);
    }

    object->applyMatrix4(_m1);

    object->updateWorldMatrix(false, false);

    this->add(object);

    return *this;
}

Vector3 &Object3D::getWorldPosition(Vector3 &target) {
    // if ( target === undefined ) {

    // 	console.warn( 'THREE.Object3D: .getWorldPosition() target is now
    // required' ); 	target = new Vector3();

    // }

    this->updateWorldMatrix(true, false);

    return target.setFromMatrixPosition(this->matrixWorld);
}

Quaternion &Object3D::getWorldQuaternion(Quaternion &target) {
    // if ( target === undefined ) {

    // 	console.warn( 'THREE.Object3D: .getWorldQuaternion() target is now
    // required' ); 	target = new Quaternion();

    // }

    Vector3 _position, _scale;

    this->updateWorldMatrix(true, false);

    this->matrixWorld.decompose(_position, target, _scale);

    return target;
}

Vector3 &Object3D::getWorldScale(Vector3 &target) {
    // if ( target === undefined ) {

    // 	console.warn( 'THREE.Object3D: .getWorldScale() target is now required'
    // ); 	target = new Vector3();

    // }

    this->updateWorldMatrix(true, false);

    Vector3 _position;
    Quaternion _quaternion;
    this->matrixWorld.decompose(_position, _quaternion, target);

    return target;
}

Vector3 &Object3D::getWorldDirection(Vector3 &target) {
    // if ( target === undefined ) {

    // 	console.warn( 'THREE.Object3D: .getWorldDirection() target is now
    // required' ); 	target = new Vector3();

    // }

    this->updateWorldMatrix(true, false);

    const auto e = this->matrixWorld.elements;

    return target.set(e[8], e[9], e[10]).normalize();
}

void Object3D::raycast() {}

void Object3D::traverse(std::function<void(shared_ptr_t)> &callback) {
    shared_ptr_t ptr;
    this->getSharedPtr(ptr);
    callback(ptr);

    const auto &children = this->children;

    for (auto &i : children) {
        i->traverse(callback);
    }
}

void Object3D::traverseVisible(std::function<void(shared_ptr_t)> &callback) {
    if (this->visible == false) return;
    shared_ptr_t ptr;
    this->getSharedPtr(ptr);
    callback(ptr);

    const auto children = this->children;

    for (auto &i : children) {
        i->traverseVisible(callback);
    }
}

void Object3D::traverseAncestors(
    std::function<void(shared_ptr_t)> &callback) {
    const auto parent = this->parent.lock();

    if (parent != nullptr) {
        callback(parent);

        parent->traverseAncestors(callback);
    }
}
void Object3D::updateMatrix() {
    this->matrix.compose(this->position, this->quaternion, this->scale);

    this->matrixWorldNeedsUpdate = true;
}

void Object3D::updateMatrixWorld(bool force) {
    auto originParent = this->parent.lock();
    if (this->matrixAutoUpdate) this->updateMatrix();

    if (this->matrixWorldNeedsUpdate || force) {
        if (originParent == nullptr) {
            this->matrixWorld = this->matrix;

        } else {
            this->matrixWorld.multiplyMatrices(originParent->matrixWorld,
                                               this->matrix);
        }

        this->matrixWorldNeedsUpdate = false;

        force = true;
    }

    // update children
    for (auto &i : children) {
        i->updateMatrixWorld(force);
    }
}

void Object3D::updateWorldMatrix(bool updateParents, bool updateChildren) {
    auto originParent = this->parent.lock();
    if (updateParents && originParent != nullptr) {
        originParent->updateWorldMatrix(true, false);
    }

    if (this->matrixAutoUpdate) this->updateMatrix();

    if (originParent == nullptr) {
        this->matrixWorld = this->matrix;

    } else {
        this->matrixWorld.multiplyMatrices(originParent->matrixWorld,
                                           this->matrix);
    }

    // update children

    if (updateChildren) {
        for (auto &i : children) {
            i->updateWorldMatrix(false, true);
        }
    }
}

// toJSON: function ( meta ) {

// 	// meta is a string when called from JSON.stringify
// 	const isRootObject = ( meta === undefined || typeof meta === 'string' );

// 	const output = {};

// 	// meta is a hash used to collect geometries, materials.
// 	// not providing it implies that this is the root object
// 	// being serialized.
// 	if ( isRootObject ) {

// 		// initialize meta obj
// 		meta = {
// 			geometries: {},
// 			materials: {},
// 			textures: {},
// 			images: {},
// 			shapes: {}
// 		};

// 		output.metadata = {
// 			version: 4.5,
// 			type: 'Object',
// 			generator: 'Object3D.toJSON'
// 		};

// 	}

// 	// standard Object3D serialization

// 	const object = {};

// 	object.uuid = this->uuid;
// 	object.type = this->type;

// 	if ( this->name !== '' ) object.name = this->name;
// 	if ( this->castShadow === true ) object.castShadow = true;
// 	if ( this->receiveShadow === true ) object.receiveShadow = true;
// 	if ( this->visible === false ) object.visible = false;
// 	if ( this->frustumCulled === false ) object.frustumCulled = false;
// 	if ( this->renderOrder !== 0 ) object.renderOrder = this->renderOrder;
// 	if ( JSON.stringify( this->userData ) !== '{}' ) object.userData =
// this->userData;

// 	object.layers = this->layers.mask;
// 	object.matrix = this->matrix.toArray();

// 	if ( this->matrixAutoUpdate === false ) object.matrixAutoUpdate = false;

// 	// object specific properties

// 	if ( this->isInstancedMesh ) {

// 		object.type = 'InstancedMesh';
// 		object.count = this->count;
// 		object.instanceMatrix = this->instanceMatrix.toJSON();

// 	}

// 	//

// 	function serialize( library, element ) {

// 		if ( library[ element.uuid ] === undefined ) {

// 			library[ element.uuid ] = element.toJSON( meta );

// 		}

// 		return element.uuid;

// 	}

// 	if ( this->isMesh || this->isLine || this->isPoints ) {

// 		object.geometry = serialize( meta.geometries, this->geometry );

// 		const parameters = this->geometry.parameters;

// 		if ( parameters !== undefined && parameters.shapes !== undefined
// )
// {

// 			const shapes = parameters.shapes;

// 			if ( Array.isArray( shapes ) ) {

// 				for ( let i = 0, l = shapes.length; i < l; i ++
// )
// {

// 					const shape = shapes[ i ];

// 					serialize( meta.shapes, shape );

// 				}

// 			} else {

// 				serialize( meta.shapes, shapes );

// 			}

// 		}

// 	}

// 	if ( this->material !== undefined ) {

// 		if ( Array.isArray( this->material ) ) {

// 			const uuids = [];

// 			for ( let i = 0, l = this->material.length; i < l; i ++
// )
// {

// 				uuids.push( serialize( meta.materials,
// this->material[ i ] ) );

// 			}

// 			object.material = uuids;

// 		} else {

// 			object.material = serialize( meta.materials,
// this->material
// );

// 		}

// 	}

// 	//

// 	if ( this->children.length > 0 ) {

// 		object.children = [];

// 		for ( let i = 0; i < this->children.length; i ++ ) {

// 			object.children.push( this->children[ i ].toJSON( meta
// ).object );

// 		}

// 	}

// 	if ( isRootObject ) {

// 		const geometries = extractFromCache( meta.geometries );
// 		const materials = extractFromCache( meta.materials );
// 		const textures = extractFromCache( meta.textures );
// 		const images = extractFromCache( meta.images );
// 		const shapes = extractFromCache( meta.shapes );

// 		if ( geometries.length > 0 ) output.geometries = geometries;
// 		if ( materials.length > 0 ) output.materials = materials;
// 		if ( textures.length > 0 ) output.textures = textures;
// 		if ( images.length > 0 ) output.images = images;
// 		if ( shapes.length > 0 ) output.shapes = shapes;

// 	}

// 	output.object = object;

// 	return output;

// 	// extract data from the cache hash
// 	// remove metadata on each item
// 	// and return as array
// 	function extractFromCache( cache ) {

// 		const values = [];
// 		for ( const key in cache ) {

// 			const data = cache[ key ];
// 			delete data.metadata;
// 			values.push( data );

// 		}

// 		return values;

// 	}

// },

CERAMICS_NAMESPACE_END
