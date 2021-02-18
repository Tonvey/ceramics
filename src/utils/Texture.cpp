#include "Texture.h"
#include <stb_image.h>
#include <stdexcept>
#include <memory>
using namespace std;

Texture::Texture(string fileName)
{
    this->load(fileName);
}
void Texture::load(string fileName)
{
    this->unload();
    unsigned char *data = stbi_load(fileName.c_str(),&mWidth,&mHeight,&mChannelsCount,0);
    if(!data)
    {
        throw runtime_error(stbi_failure_reason());
    }
    //因为使用STB读取出来的数据的坐标不是左上角开始，所以要转换
    unsigned char *tData = new unsigned char[mWidth*mHeight*mChannelsCount];
    unique_ptr<unsigned char[]> ptrData(tData);
    for(int row = 0 ; row < mHeight ; ++ row)
    {
        for(int col = 0 ; col < mWidth ; ++col)
        {
            for(int n = 0 ; n < mChannelsCount;++n)
            {
                tData[(row*mWidth + col)*mChannelsCount + n] = data[((mHeight-row)*mWidth + col)*mChannelsCount + n];
            }
        }
    }
    stbi_image_free(data);
    glGenTextures(1,&this->mId);
    glBindTexture(GL_TEXTURE_2D,this->mId);

    // 纹理设置
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    // 把内存中的图像信息，发送给显卡
    glTexImage2D(
                 GL_TEXTURE_2D,
                 0,
                 this->mode(),
                 this->mWidth,
                 this->mHeight,
                 0,
                 this->mode(),
                 GL_UNSIGNED_BYTE,
                 tData);
}
void Texture::unload()
{
    if(this->mId&&glIsTexture(this->mId)==GL_TRUE)
    {
        glDeleteTextures(1,&this->mId);
    }
}
Texture::Texture(Texture &&other)
{
    this->mId = other.mId;
    this->mWidth = other.mWidth;
    this->mHeight = other.mHeight;
    this->mChannelsCount = other.mChannelsCount;
    other.mId=0;
}
Texture &Texture::operator=(Texture &&other)
{
    this->mId = other.mId;
    this->mWidth = other.mWidth;
    this->mHeight = other.mHeight;
    this->mChannelsCount = other.mChannelsCount;
    other.mId=0;
    return *this;
}
int Texture::mode()const
{
    //TODO : channel count equal 1 or 2 has not implemented
    switch(mChannelsCount)
    {
    case 3:
        return GL_RGB;
    case 4:
        return GL_RGBA;
    default:
        return GL_RGB;
    }
}

Texture::~Texture()
{
    this->unload();
}
