#include <iostream>
#define CERAMICS_TEST
#include "../../src/CeramicsType.h"
#include "../TestBase.hpp"
using namespace std;
CERAMICS_NAMESPACE_USING
typedef TMatrix<float,2,2> Matrix2x2;
typedef TMatrix<float,3,3> Matrix3x3;
typedef TMatrix<float,4,4> Matrix4x4;
typedef TMatrix<float,3,2> Matrix3x2;
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
void testMatUnQuard(){
    cout<<"=============================================="<<endl;
    cout<<"testMatUnQuard"<<endl;
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
    TMatrix<float,2,2> result = {
        1+6+15,2+8+18,
        4+15+30,8+20+36,
    };
    printMatrix(result);
    cout<<bool(result == (mat1*mat2)) <<endl;
    cout<<"=============================================="<<endl;
}
void testMat2x2(){
    cout<<"=============================================="<<endl;
    cout<<"testMat2x2"<<endl;
    Matrix2x2 mat1,mat2;
    printMatrix(mat1);
    auto mat3 = mat1*mat2;
    printMatrix(mat3);
    auto mat4 = Matrix2x2();
    printMatrix(mat4);
    cout<<"=============================================="<<endl;
}
void testMat3x3(){
    cout<<"=============================================="<<endl;
    cout<<"testMat3x3"<<endl;
    Matrix3x3 mat1,mat2;
    printMatrix(mat1);
    auto mat3 = mat1*mat2;
    printMatrix(mat3);
    auto mat4 = Matrix3x3();
    printMatrix(mat4);
    printMatrix(mat4.getInverse());
    cout<<mat4.determinant()<<endl;
    cout<<"=============================================="<<endl;
}
void testMat4x4(){
    cout<<"=============================================="<<endl;
    cout<<"testMat4x4"<<endl;
    Matrix4x4 mat1,mat2;
    printMatrix(mat1);
    auto mat3 = mat1*mat2;
    printMatrix(mat3);
    auto mat4 = Matrix4x4();
    printMatrix(mat4);

    mat1 = {
        -1,0,0,0,
        0,1,0,0,
        0,0,-1,0,
        0,0,-1,1
    };
    mat2 = mat1;
    mat3 = mat1 * mat2;
    printMatrix(mat3);

    mat1 = Matrix4::makeTranslation(1,2,3);
    cout<<"makeTranslation 1,2,3"<<endl;
    printMatrix(mat1);

    mat1.identity();
    mat1.lookAt(Vector3(1,1,0),Vector3(1,1,1),Vector3(0,1,0));
    // mat1.lookAt(Vector3(0,0,0),Vector3(0,0,1),Vector3(0,1,0));
    cout<<"lookAt"<<endl;
    printMatrix(mat1);

    cout<<"=============================================="<<endl;
}
void testMatCompose(){
    cout<<"=============================================="<<endl;
    cout<<"testMatCompose"<<endl;
    Matrix4x4 mat;
    Vector3 position(1,1,1);
    Quaternion quaternion;
    Vector3 scale(1,1,1);
    mat.compose(position,quaternion,scale);
    printMatrix(mat);
    cout<<"=============================================="<<endl;
}
int main(){
    testMatUnQuard();
    testMat2x2();
    testMat3x3();
    testMat4x4();
    testMatCompose();
    return 0;
}
