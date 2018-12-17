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
    Matrix4d<Type> perspective(Type top,Type buttom,Type left,Type right,Type znear,Type zfar){
        return Matrix4d<Type>{
            2.0f*znear/(right-left),                  0.0,(right+left)/(right-left),                    0.0,
                              0.0,2.0f*znear/(top-buttom),(top+buttom)/(top-buttom),                    0.0,
                              0.0,                  0.0,(zfar+znear)/(znear-zfar),2.0f*zfar*znear/(znear-zfar),
                              0.0,                  0.0,                     -1.0,                    0.0
        };
    }

    template <class Type>
    Matrix4d<Type> perspective(Type width,Type height,Type znear,Type zfar){
        return Matrix4d<Type>{
                2.0f*znear/width,              0.0,                      0.0,                         0.0,
                             0.0,2.0f*znear/height,                      0.0,                         0.0,
                             0.0,              0.0,(znear+zfar)/(znear-zfar),2.0f*znear*zfar/(znear-zfar),
                             0.0,              0.0,                     -1.0,                         0.0
        };
    }

    template <class Type>
    Matrix4d<Type> perspective_fov(Type fov,Type aspect,Type znear,Type zfar){
        return Matrix4d<Type>{
                1.0f/(std::tan(fov/2.0f)*aspect),                    0.0,                      0.0,                         0.0,
                                           0.0,1.0f/std::tan(fov/2.0f),                      0.0,                         0.0,
                                           0.0,                    0.0,(zfar+znear)/(znear-zfar),(2.0f*zfar*znear)/(znear-zfar),
                                           0.0,                    0.0,                     -1.0,                         0.0
        };
    }

    template <class Type>
    Matrix4d<Type> ortho(Type top,Type buttom,Type left,Type right,Type znear,Type zfar){
        return Matrix4d<Type>{
            2.0f/(right-left),              0.0,              0.0,(left+right)/(left-right),
                          0.0,2.0f/(top-buttom),              0.0,(buttom+top)/(buttom-top),
                          0.0,              0.0,2.0f/(znear-zfar),(znear+zfar)/(znear-zfar),
                          0.0,              0.0,              0.0,                      1.0
        };
    }

    template <class Type>
    Matrix4d<Type> ortho(Type width,Type height,Type znear,Type zfar){
        return Matrix4d<Type>{
                2.0f/width,        0.0,              0.0,                      0.0,
                       0.0,2.0f/height,              0.0,                      0.0,
                       0.0,        0.0,2.0f/(znear-zfar),(znear+zfar)/(znear-zfar),
                       0.0,        0.0,              0.0,                     1.0
        };
    }

}

#endif
