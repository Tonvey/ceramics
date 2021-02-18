#pragma once
#include <string>
#include "../CeramicsType.h"
using namespace std;

class Texture
{
public:
    Texture()=default;
    Texture(string fileName);
    Texture(const Texture &other)=delete;
    Texture(Texture &&other);
    ~Texture();
    Texture &operator=(const Texture &other)=delete;
    Texture &operator=(Texture &&other);
    void load(string fileName);
    void unload();
    int id()const{return mId;}
    int width()const{return mWidth;}
    int height()const{return mHeight;}
    int channelCount()const{return mChannelsCount;}
    int mode()const;
private:
    GLuint mId;
    int mWidth;
    int mHeight;
    int mChannelsCount;
};
