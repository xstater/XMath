#include <iostream>
#include <vector>
#include "Vector.h"
#include "Matrix.h"
#include "Tools.h"

#include <math.h>

using namespace std;

int main(int argc,char *argv[]){

    xmath::Vector3df v = {1,2,3};
    xmath::Matrix4d<float> m1 = {
            1,1,1,1,
            1,2,3,4,
            1,4,2,1,
            2,3,4,1
    };

    xmath::Matrix4d<float> m2 = {
            1,2,3,4,
            4,3,2,1,
            1,2,3,1,
            2,1,2,1
    };

    cout<<m1*m2<<endl;

    cout<<m1.det()<<endl;
    cout<<m2.det()<<endl;

    cout<<m1.inverse()<<endl;

    xmath::Matrix2d<float> m3 = {
            1,2,
            3,4
    };
    cout<<m3.det()<<endl;

    xmath::Vector4df raw(1.0,0.0,0.0,1.0);
    auto now = xmath::rotateZ<float>(0.7858) * raw;
    cout<<now<<endl;
    return  0;
}