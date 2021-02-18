#include "../../src/utils/ApplicationBase.h"

class Application: public ApplicationBase
{
public:
    Application(int argc , char **argv)
        :ApplicationBase(argc,argv)
    {
    }

    virtual void render(double)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1.0,0,0);
        glBegin(GL_TRIANGLES);
        {
            glVertex2f(-0.5,0);
            glVertex2f(0.5,0);
            glVertex2f(0,0.5);
        }
        glEnd();
        glfwSwapBuffers(this->mWindow);
    }

};

int main(int argc,char **argv)
{
    Application app(argc,argv);
    return app.run();
}
