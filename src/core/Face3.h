#pragma once
#include <vector>

#include "../CeramicsMacro.h"
#include "../CeramicsType.h"
#include "../utils/Memory.hpp"
CERAMICS_NAMESPACE_BEGIN
class Face3
{
public:
    typedef std::vector<Vector3> normal_array_t;
    typedef std::vector<Color> color_array_t;
    size_t a, b, c, _id;
    // Force use array to store normal and color
    // Vector3 normal;
    // Color color;
    // TODO:
    SharedPtr<normal_array_t> __originalVertexNormals;

    normal_array_t vertexNormals;
    color_array_t vertexColors;
    int materialIndex;
    Face3(size_t a, size_t b, size_t c,
          normal_array_t normals = normal_array_t(),
          color_array_t colors = color_array_t(), int materialIndex = 0);
    Face3 clone() { return *this; };
    Face3 &copy(const Face3 &source);
    Face3 &operator=(const Face3 &source) { return this->copy(source); }
};
CERAMICS_NAMESPACE_END
