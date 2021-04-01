#include <string>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <memory>
#include "../../src/Ceramics.h"
#include "../../src/render/OpenGL/OpenGLUtils.h"
using namespace std;
CERAMICS_NAMESPACE_USING
#define VERTEX_FILE_NAME "shader.vert"
#define FRAG_FILE_NAME "shader.frag"
string shader_vert = R"EOF(
#version 330
layout(location=0) in vec3 vertexPosition;
layout(location=1) in vec2 uv;
uniform mat4x4 mvp;
out vec2 uvCoord;
void main()
{
    uvCoord = uv;
    gl_Position = mvp*vec4 (vertexPosition,1.0);
})EOF";

string shader_frag = R"EOF(
#version 330
out vec4 color;
in vec2 uvCoord;
uniform sampler2D myTextureSampler;
void main()
{
    color = texture(myTextureSampler,uvCoord).rgba;
})EOF";

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
    OpenGLShaderProgram *program= nullptr;
    GLuint vertexPosition;
    OpenGLVertexArrayObject *vao;
    OpenGLBuffer *vbo;
    OpenGLBuffer *ebo;
    OpenGLBuffer *uvbo;
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
        if(program!=nullptr)
        {
            program->release();
        }
        if(ebo!=nullptr)
        {
            ebo->release();
        }
        if(vbo!=nullptr)
        {
            vbo->release();
        }
        if(uvbo!=nullptr)
        {
            uvbo->release();
        }
        if(vao!=nullptr)
        {
            vao->release();
        }
    }

    void init()override
    {
        ApplicationCoreProfile::init();

        camera = CreateObject<PerspectiveCamera>();

        camera->setPosition(Vector3(0,0,10));

        camera->lookAt(Vector3(0,0,0));

        glEnable(GL_DEPTH_TEST);
        //OpenGLUtils::printWhenError("glEnable");
        CERAMICS_OPENGL_CHECK_ERROR("glEnable");

        // Accept fragment if it closer to the camera than the former one
        glDepthFunc(GL_LESS); 
        CERAMICS_OPENGL_CHECK_ERROR("glDepthFunc");
        //加载shader
        program = new OpenGLShaderProgram;
        RefUniquePtr<VertexShader> vert(new VertexShader);
        RefUniquePtr<FragmentShader> frag(new FragmentShader);
        vert->resetByString(shader_vert);
        frag->resetByString(shader_frag);
        program->linkProgram(vert.get(),frag.get());

        texture = Texture(FileUtil::getFileDirName(__FILE__) + FileUtil::pathChar + ".."  + FileUtil::pathChar + "textures" + FileUtil::pathChar +"panda.bmp");

        textureId =
            program->getAttributeLocation("myTextureSampler");
        CERAMICS_OPENGL_CHECK_ERROR("test");

        vertexPosition=
            program->getAttributeLocation("vertexPosition");

        uvId=
            program->getAttributeLocation("uv");

        //在显卡中申请内存，内存句柄是vertexbuffer
        //VAO创建
        vao = new OpenGLVertexArrayObject;

        //VBO创建
        vbo = new OpenGLBuffer();
        vbo->setTarget(EOpenGLBufferTarget::ArrayBuffer);
        vbo->setUsagePattern(EOpenGLBufferUsagePattern::StaticDraw);
        vbo->write(vertex_buffer_data,sizeof(vertex_buffer_data));

        //EBO创建
        ebo = new OpenGLBuffer();
        ebo->setTarget(EOpenGLBufferTarget::ElementArrayBuffer);
        ebo->setUsagePattern(EOpenGLBufferUsagePattern::StaticDraw);
        ebo->write(vertex_indices_data,sizeof(vertex_indices_data));

        //UVBO创建
        uvbo = new OpenGLBuffer();
        uvbo->setTarget(EOpenGLBufferTarget::ArrayBuffer);
        uvbo->setUsagePattern(EOpenGLBufferUsagePattern::StaticDraw);
        uvbo->write(uvBufferData,sizeof(uvBufferData));

        this->idMVP = program->getUniform("mvp");
    }

    void render(double elapse) override
    {
        this->computeMatrixesFromInput(elapse);
        if(mInput->getKeyDown(EKeyCode::W))
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
        program->use();
        glUniformMatrix4fv(this->idMVP,1,GL_TRUE,mvp.elements);
        CERAMICS_OPENGL_CHECK_ERROR("test");

        glClearColor(0,0,0.4,1.0);
        CERAMICS_OPENGL_CHECK_ERROR("test");
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        CERAMICS_OPENGL_CHECK_ERROR("test");

        //在draw之前一定要绑定好vao以及GL_ARRAY_BUFFER和GL_ELEMENT_ARRAY_BUFFER
        vao->bind();
        vbo->bind();
        program->enableVertexAttributeArray(vertexPosition);
        CERAMICS_OPENGL_CHECK_ERROR("test");
        program->enableVertexAttributeArray(uvId);
        CERAMICS_OPENGL_CHECK_ERROR("test");
        glVertexAttribPointer(
                               vertexPosition,
                               3,
                               GL_FLOAT,
                               GL_FALSE,
                               0,
                               (void*)0
                               );

        uvbo->bind();
        glVertexAttribPointer(
                              uvId,
                              2,
                              GL_FLOAT,
                              GL_FALSE,
                              0,
                              (void*)0
                              );
        ebo->bind();
        //最后通过glDrawElements的方式来绘制
        glDrawElements(
                       GL_TRIANGLES,
                       sizeof(vertex_indices_data)/sizeof(vertex_indices_data[0]),
                       GL_UNSIGNED_INT,
                       (void*)0);
        program->disableVertexAttributeArray(vertexPosition);
        glfwSwapBuffers(this->mWindow);
    }
};

int main(int argc,char **argv)
{
    Application app(argc,argv);
    return app.run();
}
