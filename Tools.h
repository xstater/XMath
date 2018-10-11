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
    Matrix4d<Type> scale(Type x,Type y,Type z,Type sx,Type sy,Type sz){
        return translate(-x,-y,-z) * scale(sx,sy,sz) * translate(x,y,z);
    }

    template <class Type>
    Matrix4d<Type> rotate(Type x,Type y,Type z){
        return Matrix4d<Type>{

        };
    }
}

#endif
