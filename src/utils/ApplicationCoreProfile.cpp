#include "ApplicationCoreProfile.h"
#include "../CeramicsType.h"
CERAMICS_NAMESPACE_USING

ApplicationCoreProfile::ApplicationCoreProfile(int argc, char **argv)
    :ApplicationBase(argc,argv)
{
    this->mGLMajorVersion=3;
    this->mGLMinorVersion=2;

    mEyePos = Vector3(0,0,5.0f);
    //mEyeHorizontalAngle=PI;
    // mEyeVerticalAngle=0.0f;
    // mInitialFoV=45.0f;
    // mSpeed=3.0f;
    // mMouseSpeed=0.005f;
}

void ApplicationCoreProfile::versionSelect()
{
    ApplicationBase::versionSelect();
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 
}

void ApplicationCoreProfile::computeMatrixesFromInput(double elapse)
{
    double xpos, ypos;
    glfwGetCursorPos(mWindow, &xpos, &ypos);

    // Reset mouse position for next frame
    int width,height;
    glfwGetWindowSize (mWindow, &width, &height);
    glfwSetCursorPos(mWindow, width/2, height/2);

    // Compute new orientation
    // mEyeHorizontalAngle += mMouseSpeed * float( width/2 - xpos );
    // mEyeVerticalAngle   += mMouseSpeed * float( height/2 - ypos );

    // Direction : Spherical coordinates to Cartesian coordinates conversion
    // Vector3 direction(
    //                   cos(mEyeVerticalAngle) * sin(mEyeHorizontalAngle), 
    //                   sin(mEyeVerticalAngle),
    //                   cos(mEyeVerticalAngle) * cos(mEyeHorizontalAngle)
    //                   );
    // Right vector
    // Vector3 right = Vector3(
    //                         sin(mEyeHorizontalAngle - PI/2.0f), 
    //                         0,
    //                         cos(mEyeHorizontalAngle - PI/2.0f)
    //                         );
    
    // Up vector
    //Vector3 up = right.cross(direction );

    // Move forward
    // if (glfwGetKey( mWindow, GLFW_KEY_W ) == GLFW_PRESS)
    // {
    //     mEyePos += direction * float(elapse) * mSpeed;
    // }
    // // Move backward
    // if (glfwGetKey( mWindow, GLFW_KEY_S ) == GLFW_PRESS)
    // {
    //     mEyePos -= direction * float(elapse) * mSpeed;
    // }
    // // Strafe right
    // if (glfwGetKey( mWindow, GLFW_KEY_D ) == GLFW_PRESS)
    // {
    //     mEyePos += right * float(elapse) * mSpeed;
    // }
    // // Strafe left
    // if (glfwGetKey( mWindow, GLFW_KEY_A ) == GLFW_PRESS)
    // {
    //     mEyePos -= right * float(elapse) * mSpeed;
    // }

    if(mInput->getKey(EKeyCode::W))
    {
    //     mEyePos += direction * float(elapse) * mSpeed;
        //camera->position.setPosition(Vector3());
    }
    if(mInput->getKey(EKeyCode::S))
    {
    //     mEyePos -= direction * float(elapse) * mSpeed;
    }
    if(mInput->getKey(EKeyCode::A))
    {
    //     mEyePos -= right * float(elapse) * mSpeed;
    }
    if(mInput->getKey(EKeyCode::A))
    {
    //     mEyePos += right * float(elapse) * mSpeed;
    }

    //float FoV = mInitialFoV;// - 5 * glfwGetMouseWheel(); // Now GLFW 3 requires setting up a callback for this. It's a bit too complicated for this beginner's tutorial, so it's disabled instead.

    // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    //{
    //    float near = 1;
    //    float far = 50;
    //    float zoom = 1.0;
    //    float aspect = 1.0;
    //    auto top = near * std::tan( MathUtils::DEG2RAD * 0.5 * FoV ) / zoom;
    //    auto height = 2 * top;
    //    auto width = aspect * height;
    //    auto left = - 0.5 * width;
    //    mMatProjection.makePerspective( left, left + width, top, top - height, near, far );
    //}
    //Vector3 center = mEyePos + direction;

    // Camera matrix
    //    mMatView.lookAt(
    //                    mEyePos,           // Camera is here
    //                    center, // and looks here : at the same position, plus "direction"
    //                    up                  // Head is up (set to 0,-1,0 to look upside-down)
    //                    );

}
