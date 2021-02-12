#include "Face3.h"
CERAMICS_NAMESPACE_BEGIN
Face3::Face3(size_t a, size_t b, size_t c, normal_array_t normals,
             color_array_t colors, int materialIndex) {
    this->a = a;
    this->b = b;
    this->c = c;
    this->vertexNormals = normals;
    this->vertexColors = colors;
    this->materialIndex = materialIndex;
}
Face3 &Face3::copy(const Face3 &source) {
    this->a = source.a;
    this->b = source.b;
    this->c = source.c;
    this->materialIndex = source.materialIndex;
    this->vertexNormals = source.vertexNormals;
    this->vertexColors = source.vertexColors;
    return *this;
}
CERAMICS_NAMESPACE_END