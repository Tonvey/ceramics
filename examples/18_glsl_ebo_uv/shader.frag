#version 330
out vec4 color;
in vec2 uvCoord;
uniform sampler2D myTextureSampler;
void main()
{
    color = texture(myTextureSampler,uvCoord).rgba;
}
