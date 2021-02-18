#pragma once

template <class T>
class TextureUVCoord2D
{
public:
    typedef TextureUVCoord2D<T> type;
    T u;
    T v;
};

template <class T>
class TextureUVCoord3D:public TextureUVCoord2D<T>
{
public:
    typedef TextureUVCoord3D<T> type;
    T w;
};

template <class T>
class Vertex2D
{
public:
    typedef Vertex2D<T> type;
    T x;
    T y;
};

template <class T>
class Vertex3D:public Vertex2D<T>
{
public:
    typedef Vertex3D<T> type;
    T z;
};

