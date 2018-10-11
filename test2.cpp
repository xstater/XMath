#include <iostream>
#include <vector>
#include "Vector.h"
#include "Matrix.h"

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
    return  0;
}