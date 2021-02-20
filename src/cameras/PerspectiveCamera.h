#include "Camera.h"
CERAMICS_NAMESPACE_BEGIN

class PerspectiveCamera : public Camera{
    CERAMICS_FORCE_CLASS_SHARED_CREATE_DECLARE(PerspectiveCamera)
public:
    struct View{
        bool enabled= false;
        int fullWidth= 1;
        int fullHeight= 1;
        int offsetX= 0;
        int offsetY= 0;
        int width= 1;
        int height= 1;
    }view;

    number_t fov = 50;
    number_t zoom = 1;
    number_t near = 0.1;
    number_t far = 2000;
    number_t focus = 10;
    number_t aspect;
    number_t filmGauge = 35;	// width of the film (default in millimeters)
    number_t filmOffset = 0;	// horizontal film offset (same unit as gauge)
protected:
    PerspectiveCamera(number_t fov = 50,number_t aspect = 1,number_t near = 0.1,number_t far = 2000 );
public:
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
    void setFocalLength(number_t focalLength );

    /**
     * Calculates the focal length from the current .fov and .filmGauge.
     */
    number_t getFocalLength()const ;
    number_t getEffectiveFOV()const;
    number_t getFilmWidth()const;
    number_t getFilmHeight()const ;
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
    void setViewOffset(int fullWidth,int fullHeight,int x,int y,int width,int height );
    void clearViewOffset() ;

    virtual void updateProjectionMatrix() override;
};


CERAMICS_NAMESPACE_END