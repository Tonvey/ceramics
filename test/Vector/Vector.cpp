#include <iostream>
#define CERAMICS_TEST
#include "../../src/math/TVector.hpp"
#include "../TestBase.hpp"
using namespace std;
typedef CERAMICS::TVector<float,2> Vector2;
typedef CERAMICS::TVector<float,3> Vector3;
typedef CERAMICS::TVector<float,4> Vector4;
template<class T>
void printVec(T &vec){
    cout<<'{';
    for(size_t i = 0 ; i < vec.size() ; ++i){
        if(i>0){
            cout<<',';
        }
        cout<<vec[i];
    }
    cout<<'}'<<endl;
}

void testVector2(){
    cout<<"Test Vector2"<<endl;
    Vector2 v1(1,2);
    Vector2 v2(3,4);

    printVec(v1);
    printVec(v2);

    //copy contructor
    Vector2 v1_bak = v1;
    Vector2 v2_bak = v2;
    TEST_ASSERT(v1_bak[0]==v1[0]);
    TEST_ASSERT(v1_bak[1]==v1[1]);
    TEST_ASSERT(v1_bak==v1);

    printVec(v1_bak);
    printVec(v2_bak);

    //math calculate
    v1.set(1,1);
    printVec(v1.addScalar(2));
    TEST_ASSERT(v1.x==3&&v1.y==3);
    printVec(v1.subScalar(1));
    TEST_ASSERT(v1.x==2&&v1.y==2);
    printVec(v1.multiplyScalar(2));
    TEST_ASSERT(v1.x==4&&v1.y==4);
    printVec(v1.divideScalar(2));
    TEST_ASSERT(v1.x==2&&v1.y==2);

    v1.set(1,1);
    v2.set(2,2);
    printVec(v2.add(v1));
    TEST_ASSERT(v2.x==3&&v2.y==3);
    auto v3 = v2.normalize();
    printVec(v3);
    cout<<v3.length()<<endl;
    TEST_ASSERT(v3.length()==1.0);
}
int main(){
    testVector2();
    return 0;
}
