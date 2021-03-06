#include "PerspectiveCamera.h"
#include <algorithm>
CERAMICS_NAMESPACE_BEGIN

void PerspectiveCamera::setFov(Real fov)
{
    mFov = fov;
    mProjectionMatrixNeedUpdate=true;
}
void PerspectiveCamera::setZoom(Real zoom)
{
    mZoom = zoom;
    mProjectionMatrixNeedUpdate=true;
}
void PerspectiveCamera::setNear(Real near)
{
    mNear = near;
    mProjectionMatrixNeedUpdate=true;
}
void PerspectiveCamera::setFar(Real far)
{
    mFar = far;
    mProjectionMatrixNeedUpdate=true;
}
void PerspectiveCamera::setFocus(Real focus)
{
    mFocus = focus;
    mProjectionMatrixNeedUpdate=true;
}
void PerspectiveCamera::setAspect(Real aspect)
{
    mAspect = aspect;
    mProjectionMatrixNeedUpdate=true;
}
void PerspectiveCamera::setFilmGauge(Real filmGauge)
{
    mFilmGauge = filmGauge;
    mProjectionMatrixNeedUpdate=true;
}
void PerspectiveCamera::setFilmOffset(Real filmOffset)
{
    mFilmOffset = filmOffset;
    mProjectionMatrixNeedUpdate=true;
}
PerspectiveCamera::PerspectiveCamera(Real fov,Real aspect,Real near,Real far) {

    this->mFov = fov;
    this->mNear = near;
    this->mFar = far;
    this->mAspect = aspect;
    this->mProjectionMatrixNeedUpdate = true;
}
/* copy: function ( source, recursive ) { */

/* 	Camera.prototype.copy.call( this, source, recursive ); */

/* 	this->fov = source.fov; */
/* 	this->zoom = source.zoom; */

/* 	this->near = source.near; */
/* 	this->far = source.far; */
/* 	this->focus = source.focus; */

/* 	this->aspect = source.aspect; */
/* 	this->view = source.view === null ? null : Object.assign( {}, source.view ); */

/* 	this->filmGauge = source.filmGauge; */
/* 	this->filmOffset = source.filmOffset; */

/* 	return this; */

/* }, */

/**
 * Sets the FOV by focal length in respect to the current .filmGauge.
 *
 * The default film gauge is 35, so that the focal length can be specified for
 * a 35mm (full frame) camera.
 *
 * Values for focal length and film gauge must have the same unit.
 */
void PerspectiveCamera::setFocalLength(Real focalLength )
{

    /** see {@link http://www.bobatkins.com/photography/technical/field_of_view.html} */
    const auto vExtentSlope = 0.5 * this->getFilmHeight() / focalLength;

    this->mFov = MathUtils::RAD2DEG * 2 * std::atan( vExtentSlope );
    this->mProjectionMatrixNeedUpdate = true;
    this->updateProjectionMatrix();

}

/**
 * Calculates the focal length from the current .fov and .filmGauge.
 */
Real PerspectiveCamera::getFocalLength()const
{

    const auto vExtentSlope = std::tan( MathUtils::DEG2RAD * 0.5 * this->mFov );

    return 0.5 * this->getFilmHeight() / vExtentSlope;

}

Real PerspectiveCamera::getEffectiveFOV()const
{

    return MathUtils::RAD2DEG * 2 * std::atan(
                                              std::tan( MathUtils::DEG2RAD * 0.5 * this->mFov ) / this->mZoom );

}

Real PerspectiveCamera::getFilmWidth()const
{

    // film not completely covered in portrait format (aspect < 1)
    return this->mFilmGauge * std::min( this->mAspect, 1.0f );

}

Real PerspectiveCamera::getFilmHeight()const
{

    // film not completely covered in landscape format (aspect > 1)
    return this->mFilmGauge / std::max( this->mAspect, 1.0f );

}

/**
 * Sets an offset in a larger frustum. This is useful for multi-window or
 * multi-monitor/multi-machine setups.
 *
 * For example, if you have 3x2 monitors and each monitor is 1920x1080 and
 * the monitors are in grid like this
 *
 *   +---+---+---+
 *   | A | B | C |
 *   +---+---+---+
 *   | D | E | F |
 *   +---+---+---+
 *
 * then for each monitor you would call it like this
 *
 *   const w = 1920;
 *   const h = 1080;
 *   const fullWidth = w * 3;
 *   const fullHeight = h * 2;
 *
 *   --A--
 *   camera.setViewOffset( fullWidth, fullHeight, w * 0, h * 0, w, h );
 *   --B--
 *   camera.setViewOffset( fullWidth, fullHeight, w * 1, h * 0, w, h );
 *   --C--
 *   camera.setViewOffset( fullWidth, fullHeight, w * 2, h * 0, w, h );
 *   --D--
 *   camera.setViewOffset( fullWidth, fullHeight, w * 0, h * 1, w, h );
 *   --E--
 *   camera.setViewOffset( fullWidth, fullHeight, w * 1, h * 1, w, h );
 *   --F--
 *   camera.setViewOffset( fullWidth, fullHeight, w * 2, h * 1, w, h );
 *
 *   Note there is no reason monitors have to be the same size or in a grid.
 */
void PerspectiveCamera::setViewOffset(int fullWidth,int fullHeight,int x,int y,int width,int height )
{

    this->mAspect = Real(fullWidth) / Real(fullHeight);
    this->view.enabled = true;
    this->view.fullWidth = fullWidth;
    this->view.fullHeight = fullHeight;
    this->view.offsetX = x;
    this->view.offsetY = y;
    this->view.width = width;
    this->view.height = height;

    this->mProjectionMatrixNeedUpdate = true;

    this->updateProjectionMatrix();

}

void PerspectiveCamera::clearViewOffset()
{

    this->view.enabled = false;
    this->mProjectionMatrixNeedUpdate = true;

    this->updateProjectionMatrix();

}

void PerspectiveCamera::updateProjectionMatrix()
{

    if(!this->mProjectionMatrixNeedUpdate)
        return;
    this->mProjectionMatrixNeedUpdate=false;

    auto near = this->mNear;
    auto far = this->mFar;
    auto top = near * std::tan( MathUtils::DEG2RAD * 0.5 * this->mFov ) / this->mZoom;
    auto height = 2 * top;
    auto width = this->mAspect * height;
    auto left = - 0.5 * width;
    const auto view = this->view;

    if (this->view.enabled )
    {

        const auto fullWidth = view.fullWidth,
            fullHeight = view.fullHeight;

        left += view.offsetX * width / fullWidth;
        top -= view.offsetY * height / fullHeight;
        width *= view.width / fullWidth;
        height *= view.height / fullHeight;

    }

    const auto skew = this->mFilmOffset;
    if ( skew != 0 ) left += near * skew / this->getFilmWidth();

    this->mProjectionMatrix = Matrix4::makePerspective( left, left + width, top, top - height, near, far );

    this->mProjectionMatrixInverse = this->mProjectionMatrix.getInverse();

}
CERAMICS_NAMESPACE_END
