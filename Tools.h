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

}

#endif
