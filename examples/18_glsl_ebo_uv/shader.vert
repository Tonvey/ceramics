#version 330
//属性，这个属性用来获取定点位置，具体的顶点值，由C++传值
layout(location=0) in vec3 vertexPosition;
layout(location=1) in vec2 uv;
uniform mat4x4 mvp;
out vec2 uvCoord;
//shader主程序
void main()
{
    uvCoord = uv;
    gl_Position = mvp*vec4 (vertexPosition,1.0);
}
