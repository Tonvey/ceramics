#include <iostream>
#define THREE_TEST
#include "../../src/math/TMatrix.hpp"
#include "../TestBase.hpp"
using namespace std;
using THREE::TVector;
using THREE::TMatrix;
typedef TVector<float,2> Vector2;
typedef TVector<float,3> Vector3;
typedef TVector<float,4> Vector4;
typedef TMatrix<float,2,2> Matrix2x2;
typedef TMatrix<float,3,3> Matrix3x3;
typedef TMatrix<float,4,4> Matrix4x4;
typedef TMatrix<float,3,2> Matrix3x2;
template<class T>
void printMatrix(T mat){
    for(size_t r = 0 ; r < mat.row(); ++r){
        cout<<'|';
        for(size_t c = 0 ; c < mat.col(); ++c){
            cout << mat[r * mat.col() + c];
            if(c!=mat.col()-1){
                cout<<",\t";
            }
        }
        cout<<'|'<<endl;
    }
}
void testMatUnQuard(){
    TMatrix<float,2,3> mat1 = {
                               1,2,3,
                               4,5,6
    };
    TMatrix<float,3,2> mat2 = {
                               1,2,
                               3,4,
                               5,6
    };
    printMatrix(mat1);
    printMatrix(mat2);
    printMatrix(mat1*mat2);
}
void testMat2x2(){
    Matrix2x2 mat1,mat2;
    printMatrix(mat1);
    auto mat3 = mat1*mat2;
    printMatrix(mat3);
    auto mat4 = Matrix2x2();
    printMatrix(mat4);
}
void testMat3x3(){
    Matrix3x3 mat1,mat2;
    printMatrix(mat1);
    auto mat3 = mat1*mat2;
    printMatrix(mat3);
    auto mat4 = Matrix3x3();
    printMatrix(mat4);
    printMatrix(mat4.getInverse());
    cout<<mat4.determinant()<<endl;
}
void testMat4x4(){
    Matrix4x4 mat1,mat2;
    printMatrix(mat1);
    auto mat3 = mat1*mat2;
    printMatrix(mat3);
    auto mat4 = Matrix4x4();
    printMatrix(mat4);
}
int main(){
    testMatUnQuard();
    testMat2x2();
    testMat3x3();
    testMat4x4();
    return 0;
}
