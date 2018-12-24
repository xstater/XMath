#ifndef _XMATH_TOOLS_H_
#define _XMATH_TOOLS_H_

#include "Matrix.h"

namespace xmath{
    template <class Type>
    Matrix4d<Type> translate(Type x,Type y,Type z){
        Matrix4d<Type> mat;
        mat(3, 0) = x;
        mat(3, 1) = y;
        mat(3, 2) = z;
        mat(3, 3) = 1.0;
        return mat;
    }
    
    template <class Type>
    Matrix4d<Type> scale(Type x,Type y,Type z){
        Matrix4d<Type> mat;
        mat(0,0) = x;
        mat(1,1) = y;
        mat(2,2) = z;
        return mat;
    }
    template <class Type>
    Matrix4d<Type> rotate(Type xrad,Type yrad,Type zrad){
        Matrix4d<Type> ma, mb, mc;
        Type ac = cos(xrad);
        Type as = sin(xrad);
        Type bc = cos(yrad);
        Type bs = sin(yrad);
        Type cc = cos(zrad);
        Type cs = sin(zrad);

        ma(1, 1) = ac;
        ma(2, 1) = as;
        ma(1, 2) = -as;
        ma(2, 2) = ac;

        mb(0, 0) = bc;
        mb(2, 0) = -bs;
        mb(0, 2) = bs;
        mb(2, 2) = bc;

        mc(0, 0) = cc;
        mc(1, 0) = cs;
        mc(0, 1) = -cs;
        mc(1, 1) = cc;
        
        Matrix4d<Type> ret = ma * mb * mc;

        return ret;
    }
    template <class Type>
    Matrix4d<Type> lookAt(const Vector3d<Type> &eye,const Vector3d<Type> &target,const Vector3d<Type> &up){
        Vector3d<Type> forward, side, up2;
        Matrix4d<Type> mat;

        forward = target - eye;
        up2 = up;

        forward.normalize();
        
        side = forward.cross(up);
        side.normalize();
        
        up2 = side.cross(forward);

        mat(0, 0) = side.x;
        mat(1, 0) = side.y;
        mat(2, 0) = side.z;

        mat(0, 1) = up2.x;
        mat(1, 1) = up2.y;
        mat(2, 1) = up2.z;

        mat(0, 2) = -forward.x;
        mat(1, 2) = -forward.y;
        mat(2, 2) = -forward.z;

        mat = mat * translate(-eye.x, -eye.y, -eye.z);
        return mat;
    }
    template <class Type>
    Matrix4d<Type> frustum(Type left,Type right,Type bottom,Type top,Type znear,Type zfar){
        Matrix4d<Type> mat;

        const Type invWidth = 1.0 / (right - left);
        const Type invHeight = 1.0 / (top - bottom);
        const Type invDepth = 1.0 / (zfar - znear);

        const Type twoZNear = 2 * znear;

        mat(0,0) = twoZNear * invWidth;
        mat(1,1) = twoZNear * invHeight;

        mat(2,0) = (right + left) * invWidth;
        mat(2,1) = (top + bottom) * invHeight;
        mat(2,2) = - (zfar + znear) * invDepth;
        mat(2,3) = -1;

        mat(3,2) = - twoZNear * zfar * invDepth;
        mat(3,3) = 0;

        return mat;
    }
    template <class Type>
    Matrix4d<Type> ortho(Type left,Type right,Type bottom,Type top,Type znear,Type zfar){
        const Type invWidth = 1.0 / (right  - left);
        const Type invHeight = 1.0 / (top - bottom);
        const Type invDepth = 1.0 / (zfar - znear);

        Matrix4d<Type> mat;

        mat(0,0) = 2 * invWidth;
        mat(1,1) = 2 * invHeight;
        mat(2,2) = -2 * invDepth;

        mat(3,0) = -(right + left) * invWidth;
        mat(3,1) = -(top + bottom) * invHeight;
        mat(3,2) = -(zfar + znear) * invDepth;

        return mat;
    }
}

#endif //_XMATH_TOOLS_H_