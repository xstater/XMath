#ifndef _XMATH_TOOLS_H_
#define _XMATH_TOOLS_H_

#include <cmath>
#include "Matrix.h"

namespace xmath{
    template <class Type>
    Matrix4d<Type> translate(Type x,Type y,Type z){
        return Matrix4d<Type>{
            1.0, 0.0, 0.0,   x,
            0.0, 1.0, 0.0,   y,
            0.0, 0.0, 1.0,   z,
            0.0, 0.0, 0.0, 1.0
        };
    }

    template <class Type>
    Matrix4d<Type> scale(Type x,Type y,Type z){
        return Matrix4d<Type>{
            x,   0.0, 0.0, 0.0,
            0.0,   y, 0.0, 0.0,
            0.0, 0.0,   z, 0.0,
            0.0, 0.0, 0.0, 1.0
        };
    }


    template <class Type>
    Matrix4d<Type> rotateX(Type angle){
        return Matrix4d<Type>{
            1.0,             0.0,             0.0, 0.0,
            0.0, std::cos(angle),-std::sin(angle), 0.0,
            0.0, std::sin(angle), std::cos(angle), 0.0,
            0.0,             0.0,             0.0, 1.0
        };
    }

    template <class Type>
    Matrix4d<Type> rotateY(Type angle){
        return Matrix4d<Type>{
            std::cos(angle), 0.0, std::sin(angle), 0.0,
                        0.0, 1.0,             0.0, 0.0,
           -std::sin(angle), 0.0, std::cos(angle), 0.0,
                        0.0, 0.0,             0.0, 1.0
        };
    }

    template <class Type>
    Matrix4d<Type> rotateZ(Type angle){
        return Matrix4d<Type>{
                std::cos(angle),-std::sin(angle), 0.0, 0.0,
                std::sin(angle), std::cos(angle), 0.0, 0.0,
                            0.0,             1.0, 0.0, 0.0,
                            0.0,             0.0, 0.0, 1.0
        };
    }

    template <class Type>
    Matrix4d<Type> perspective(Type top,Type buttom,Type left,Type right,Type near,Type far){
        return Matrix4d<Type>{
            2.0*near/(right-left),                  0.0,(right+left)/(right-left),                    0.0,
                              0.0,2.0*near/(top-buttom),(top+buttom)/(top-buttom),                    0.0,
                              0.0,                  0.0,    (near+far)/(near-far),2.0*near*far/(near-far),
                              0.0,                  0.0,                     -1.0,                    0.0
        };
    }

    template <class Type>
    Matrix4d<Type> perspective(Type width,Type height,Type near,Type far){
        return Matrix4d<Type>{
                2.0*near/width,            0.0,                  0.0,                    0.0,
                           0.0,2.0*near/height,                  0.0,                    0.0,
                           0.0,            0.0,(near+far)/(near-far),2.0*near*far/(near-far),
                           0.0,            0.0,                 -1.0,                    0.0
        };
    }

    template <class Type>
    Matrix4d<Type> perspective_fov(Type fov,Type aspect,Type near,Type far){
        return Matrix4d<Type>{
                1.0/std::tan(fov/2.0)/aspect,                  0.0,                  0.0,                    0.0,
                                         0.0,1.0/std::tan(fov/2.0),                  0.0,                    0.0,
                                         0.0,                  0.0,(near+far)/(near-far),2.0*near*far/(near-far),
                                         0.0,                  0.0,                 -1.0,                    0.0
        };
    }

    template <class Type>
    Matrix4d<Type> ortho(Type top,Type buttom,Type left,Type right,Type near,Type far){
        return Matrix4d<Type>{
            2.0/(right-left),             0.0,           0.0,(left+right)/(left-right),
                         0.0,2.0/(top-buttom),           0.0,(buttom+top)/(buttom-top),
                         0.0,             0.0,2.0/(near-far),    (near+far)/(near-far),
                         0.0,             0.0,           0.0,                      1.0
        };
    }

    template <class Type>
    Matrix4d<Type> ortho(Type width,Type height,Type near,Type far){
        return Matrix4d<Type>{
                2.0/width,       0.0,           0.0,                  0.0,
                      0.0,2.0/height,           0.0,                  0.0,
                      0.0,       0.0,2.0/(near-far),(near+far)/(near-far),
                      0.0,       0.0,           0.0,                  1.0
        };
    }

}

#endif
