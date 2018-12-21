#ifndef _XMATH_TOOLS_H_
#define _XMATH_TOOLS_H_

#include <cmath>
#include "Matrix.h"

#include <iostream>
using namespace std;

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
    Matrix4d<Type> rotate(Type x,Type y,Type z){
        return Matrix4d<Type>{
            1.0,         0.0,        0.0,0.0,
            0.0, std::cos(x),std::sin(x),0.0,
            0.0,-std::sin(x),std::cos(x),0.0,
            0.0,         0.0,        0.0,1.0
        } * Matrix4d<Type>{
            std::cos(y),0.0,-std::sin(y),0.0,
                    0.0,1.0,         0.0,0.0,
            std::sin(y),0.0, std::cos(y),0.0,
                    0.0,0.0,         0.0,1.0
        } * Matrix4d<Type>{
            std::cos(z),std::sin(z),0.0,0.0,
           -std::sin(z),std::cos(z),0.0,0.0,
                    0.0,        0.0,1.0,0.0,
                    0.0,        0.0,0.0,1.0
        };
    }

    template <class Type>
    Matrix4d<Type> lookAt(const Vector3d<Type> &eye,const Vector3d<Type> &target,const Vector3d<Type> &up){
        auto forward = target - eye;
        forward /= forward.length();//normalize

        auto side = forward.cross(up);
        side /= side.length();//normalize

        auto up2 = side.cross(forward);
        
        Matrix4d<Type> view{
                side.x,    side.y,    side.z,0.0,
                 up2.x,     up2.y,     up2.z,0.0,
            -forward.x,-forward.y,-forward.z,0.0,
                   0.0,       0.0,       0.0,1.0
        };

        return view * translate<Type>(-eye.x,-eye.y,-eye.z);
    }

    template <class Type>
    Matrix4d<Type> frustum(Type top,Type buttom,Type left,Type right,Type znear,Type zfar){
        return Matrix4d<Type>{
            static_cast<Type>(2.0)*znear/(right-left),                                      0.0,(right+left)/(right-left),                                           0.0,
                                                  0.0,static_cast<Type>(2.0)*znear/(top-buttom),(top+buttom)/(top-buttom),                                           0.0,
                                                  0.0,                                      0.0,(zfar+znear)/(znear-zfar),static_cast<Type>(2.0)*zfar*znear/(znear-zfar),
                                                  0.0,                                      0.0,                     -1.0,                                           0.0
        };
    }

    template <class Type>
    Matrix4d<Type> frustum(Type width,Type height,Type znear,Type zfar){
        return Matrix4d<Type>{
            static_cast<Type>(2.0)*znear/width,                                0.0,                      0.0,                                           0.0,
                                           0.0,static_cast<Type>(2.0)*znear/height,                      0.0,                                           0.0,
                                           0.0,                                0.0,(znear+zfar)/(znear-zfar),static_cast<Type>(2.0)*znear*zfar/(znear-zfar),
                                           0.0,                                0.0,                     -1.0,                                           0.0
        };
    }

    template <class Type>
    Matrix4d<Type> frustum_fov(Type fov,Type aspect,Type znear,Type zfar){
        return Matrix4d<Type>{
            static_cast<Type>(1.0)/(std::tan(fov/static_cast<Type>(2.0))*aspect),0.0,0.0,0.0,
            0.0,static_cast<Type>(1.0)/std::tan(fov/ static_cast<Type>(2.0)),0.0,0.0,
            0.0,0.0,(zfar+znear)/(znear-zfar),(static_cast<Type>(2.0)*zfar*znear)/(znear-zfar),
            0.0,0.0,-1.0,0.0
        };
    }

    template <class Type>
    Matrix4d<Type> ortho(Type top,Type buttom,Type left,Type right,Type znear,Type zfar){
        return Matrix4d<Type>{
                static_cast<Type>(2.0)/(right-left),              0.0,              0.0,(left+right)/(left-right),
                          0.0,static_cast<Type>(2.0)/(top-buttom),              0.0,(buttom+top)/(buttom-top),
                          0.0,              0.0, static_cast<Type>(2.0)/(znear-zfar),(znear+zfar)/(znear-zfar),
                          0.0,              0.0,              0.0,                      1.0
        };
    }

    template <class Type>
    Matrix4d<Type> ortho(Type width,Type height,Type znear,Type zfar){
        return Matrix4d<Type>{
                static_cast<Type>(2.0)/width,        0.0,              0.0,                      0.0,
                       0.0,static_cast<Type>(2.0)/height,              0.0,                      0.0,
                       0.0,        0.0, static_cast<Type>(2.0)/(znear-zfar),(znear+zfar)/(znear-zfar),
                       0.0,        0.0,              0.0,                     1.0
        };
    }

}

#endif
