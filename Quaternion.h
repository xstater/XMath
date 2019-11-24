#ifndef _XMATH_QUATERNION_H_
#define _XMATH_QUATERNION_H_

#include "Vector.h"

namespace xmath{
    template <class Type>
    class Quaternion : public Vector<Type,4>{
    public:
        Quaternion():Vector<Type,4>(){}
        explicit Quaternion(Type val):Vector<Type,4>(val){}
        explicit Quaternion(const Type *ptr):Vector<Type,4>(ptr){}
        explicit Quaternion(std::initializer_list<Type> list):Vector<Type,4>(list){}
        explicit Quaternion(const Matrix<Type,4,4> &mat)
            :Vector<Type,4>(){
            (*this)[3] = std::sqrt(1.0 + mat(0,0) + mat(1,1) + mat(2,2))/2.0;
            (*this)[0] = (mat(2,1) - mat(1,2)) / (*this)[3] / 4.0;
            (*this)[1] = (mat(0,2) - mat(2,0)) / (*this)[3] / 4.0;
            (*this)[2] = (mat(1,0) - mat(0,1)) / (*this)[3] / 4.0;
        }
        Quaternion(const Quaternion &vec) = default;
        Quaternion(Quaternion &&) = default;
        ~Quaternion() = default;

        Quaternion &operator=(const Quaternion &mat) = default;
        Quaternion &operator=(Quaternion &&) noexcept = default;

        Quaternion cross(const Quaternion &qut)const noexcept{
            return Quaternion{
                    (*this)[3] * qut[0] + (*this)[0] * qut[3] + (*this)[1] * qut[2] - (*this)[2] * qut[1],
                    (*this)[3] * qut[1] + (*this)[1] * qut[3] + (*this)[2] * qut[0] - (*this)[0] * qut[2],
                    (*this)[3] * qut[2] + (*this)[2] * qut[3] + (*this)[0] * qut[1] - (*this)[1] * qut[0],
                    (*this)[3] * qut[3] - (*this)[0] * qut[0] - (*this)[1] * qut[1] - (*this)[2] * qut[2]
            };
        }

        Quaternion conjugate()const noexcept{
            return Quaternion{-(*this)[0],-(*this)[1],-(*this)[2],(*this)[3]};
        }

        Quaternion inverse()const noexcept{
            return Quaternion(conjugate() / this->length());
        }

        Quaternion normalize()const noexcept{
            return Quaternion(this->operator/(this->length()));
        }

        Matrix<Type,4,4> rotate()const noexcept{
            Type x = (*this)[0];
            Type y = (*this)[1];
            Type z = (*this)[2];
            Type w = (*this)[3];
            return Matrix<Type,4,4>{
                1.0-2.0*y*y-2.0*z*z,2.0*x*y-2.0*z*w,2.0*x*z+2.0*y*w,0.0,
                2.0*x*y+2.0*z*w,1.0-2.0*x*x-2.0*z*z,2.0*y*z-2.0*x*w,0.0,
                2.0*x*z-2.0*y*w,2.0*y*z+2.0*x*w,1.0-2.0*x*x-2.0*y*y,0.0,
                0.0,0.0,0.0,1.0
            };
        }
    protected:
    private:
    };

    ///xyzw
    using Quaternionf = Quaternion<float>;
    using Quaterniond = Quaternion<double>;
    using Quaternioni = Quaternion<int>;
    using Quaternionui = Quaternion<unsigned int>;
}

#endif //XMATH_QUATERNION_H_