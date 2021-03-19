#include <string>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <memory>
#include "../../src/utils/ApplicationCoreProfile.h"
#include "../../src/utils/FileUtil.h"
#include "../../src/utils/Texture.h"
#include "../../src/cameras/PerspectiveCamera.h"
using namespace std;
CERAMICS_NAMESPACE_USING
#define VERTEX_FILE_NAME "shader.vert"
#define FRAG_FILE_NAME "shader.frag"

const GLfloat vertex_buffer_data[]={
    0.5f, 0.5f, 0.0f,   // 右上角
    0.5f, -0.5f, 0.0f,  // 右下角
    -0.5f, -0.5f, 0.0f, // 左下角
    -0.5f, 0.5f, 0.0f   // 左上角
};
//只要跟上面坐标对上就行
const GLfloat uvBufferData[]={
    1.0f,1.0f,
    1.0f,0.0f,
    0.0f,0.0f,
    0.0f,1.0f,
};
const GLuint vertex_indices_data[]={
    // 起始于0!
    0, 3, 1, // 第一个三角形
    1, 3, 2  // 第二个三角形
};
template<class T>
void printMatrix(T mat){
    for(size_t r = 0 ; r < mat.numOfRows(); ++r){
        cout<<'|';
        for(size_t c = 0 ; c < mat.numOfCols(); ++c){
            cout << mat[r * mat.numOfCols() + c];
            if(c!=mat.numOfCols()-1){
                cout<<",\t";
            }
        }
        cout<<'|'<<endl;
    }
    cout<<endl;
}
void printMatrix4(const Matrix4 &mat){
    printMatrix(mat);
}

class Application: public ApplicationCoreProfile
{
private:
    ShaderProgram program;
    GLuint vertexPosition;
    GLuint vbo;
    GLuint vao;
    GLuint ebo;
    GLuint uvbo;
    GLuint uvId;
    GLuint textureId;
    Texture texture;
    GLuint idMVP;
    PerspectiveCamera *camera;
public:

    Application(int argc , char **argv)
        :ApplicationCoreProfile(argc,argv)
    {
    }
    ~Application()
    {
        camera->release();
        if(glIsBuffer(ebo)==GL_TRUE)
        {
            cout<<"Delete ebo buffer"<<endl;
            glDeleteBuffers(1,&ebo);
        }
        if(glIsBuffer(vbo)==GL_TRUE)
        {
            cout<<"Delete vbo buffer"<<endl;
            glDeleteBuffers(1,&vbo);
        }
        if(glIsBuffer(uvbo)==GL_TRUE)
        {
            cout<<"Delete uvbo buffer"<<endl;
            glDeleteBuffers(1,&uvbo);
        }
        if(glIsVertexArray(vao)==GL_TRUE)
        {
            cout<<"Delete vao buffer"<<endl;
            glDeleteVertexArrays(1,&vao);
        }
    }

    void init()override
    {
        ApplicationCoreProfile::init();

        camera = CreateObject<PerspectiveCamera>();

        camera->setPosition(Vector3(0,0,10));

        camera->lookAt(Vector3(0,0,0));

        glEnable(GL_DEPTH_TEST);

        // Accept fragment if it closer to the camera than the former one
        glDepthFunc(GL_LESS); 
        //加载shader
        program = loadShader(
                             FileUtil::getFileDirName(__FILE__) + FileUtil::pathChar + VERTEX_FILE_NAME,
                             FileUtil::getFileDirName(__FILE__) + FileUtil::pathChar + FRAG_FILE_NAME);

        //加载纹理图片
        glEnable(GL_TEXTURE_2D);
        texture = Texture(FileUtil::getFileDirName(__FILE__) + FileUtil::pathChar + ".."  + FileUtil::pathChar + "textures" + FileUtil::pathChar +"panda.bmp");

        textureId =
            program.getAttr("myTextureSampler");

        vertexPosition=
            program.getAttr("vertexPosition");

        uvId=
            program.getAttr("uv");

        //在显卡中申请内存，内存句柄是vertexbuffer
        //VAO创建
        glGenVertexArrays(1,&vao);

        //VBO创建
        glGenBuffers(1, &vbo);
        //此时的绑定只是为了传入数据，没有其他太多的作用
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(
            GL_ARRAY_BUFFER,
            sizeof(vertex_buffer_data),
            vertex_buffer_data,
            GL_STATIC_DRAW);
        //解绑
        glBindBuffer(GL_ARRAY_BUFFER,0);

        //EBO创建
        glGenBuffers(1, &ebo);
        //此时的绑定只是为了传入数据，没有其他太多的作用
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        //解绑
        glBufferData(
                     GL_ELEMENT_ARRAY_BUFFER,
                     sizeof(vertex_indices_data),
                     vertex_indices_data,
                     GL_STATIC_DRAW);

        //UVBO创建
        glGenBuffers(1,&uvbo);
        glBindBuffer(GL_ARRAY_BUFFER,uvbo);
        glBufferData(
                     GL_ARRAY_BUFFER,
                     sizeof(uvBufferData),
                     uvBufferData,
                     GL_STATIC_DRAW
                     );
        glBindBuffer(GL_ARRAY_BUFFER,0);


        //习惯性的解绑
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

        this->idMVP = program.getUniform("mvp");
    }

    void render(double elapse) override
    {
        this->computeMatrixesFromInput(elapse);
        if(mInput->getKeyDown(KeyCode::W))
        {
            camera->setPosition(camera->getPosition()+Vector3(elapse,0,0));
        }
        Matrix4 matModel;
        Matrix4 projectionMatrix = camera->getProjectionMatrix();
        Matrix4 viewMatrix = camera->getMatrixWorldInverse();

        cout<<"modelMatrix:"<<endl;
        printMatrix(matModel);
        cout<<"projectionMatrix:"<<endl;
        printMatrix(projectionMatrix);
        cout<<"viewMatrix:"<<endl;
        printMatrix(viewMatrix);
        Matrix4 mvp = projectionMatrix * viewMatrix * matModel;
        cout<<"mvp:"<<endl;
        printMatrix(mvp);
        glUniformMatrix4fv(this->idMVP,1,GL_TRUE,&mvp[0]);

        glClearColor(0,0,0.4,1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        program.use();
        glEnableVertexAttribArray(vertexPosition);
        glEnableVertexAttribArray(uvId);


        //在draw之前一定要绑定好vao以及GL_ARRAY_BUFFER和GL_ELEMENT_ARRAY_BUFFER
        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER,this->vbo);
        glVertexAttribPointer(
                               vertexPosition,
                               3,
                               GL_FLOAT,
                               GL_FALSE,
                               0,
                               (void*)0
                               );

        glBindBuffer(GL_ARRAY_BUFFER,this->uvbo);
        glVertexAttribPointer(
                              uvId,
                              2,
                              GL_FLOAT,
                              GL_FALSE,
                              0,
                              (void*)0
                              );
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,this->ebo);
        //最后通过glDrawElements的方式来绘制
        glDrawElements(
                       GL_TRIANGLES,
                       sizeof(vertex_indices_data)/sizeof(vertex_indices_data[0]),
                       GL_UNSIGNED_INT,
                       (void*)0);
        glDisableVertexAttribArray(vertexPosition);
        glfwSwapBuffers(this->mWindow);
    }
};

int main(int argc,char **argv)
{
    Application app(argc,argv);
    return app.run();
}
