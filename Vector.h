#ifndef _XMATH_VECTOR_H_
#define _XMATH_VECTOR_H_

#include <cmath>
#include "Matrix.h"

namespace xmath{
    template <class Type,size_t Length>
    class Vector : public Matrix<Type,1,Length>{
    public:
        Vector():Matrix<Type,1,Length>(){}
        explicit Vector(Type val):Matrix<Type,1,Length>(val){}
        explicit Vector(const Type *ptr):Matrix<Type,1,Length>(ptr){}
        template <class Iterator>
        explicit Vector(Iterator beg,Iterator end):Matrix<Type,1,Length>(beg,end){}
        explicit Vector(std::initializer_list<Type> list):Matrix<Type,1,Length>(list){}
        template <class Type2,size_t Row2,size_t Col2>
        explicit Vector(const Matrix<Type2,Row2,Col2> &matrix):Matrix<Type,1,Length>(matrix){}
        Vector(const Vector &vec) = default;
        Vector(Vector &&) = default;
        ~Vector() = default;

        Vector &operator=(const Vector &mat) = default;
        Vector &operator=(Vector &&) noexcept = default;

        Type dot(const Vector &vec) const noexcept{
            Type ans = 0;
            for(size_t i = 0;i < Length; ++i){
                ans += this->m_data[i] * vec[i];
            }
            return ans;
        }

        template <size_t Length2>
        auto cross(const Vector<Type,Length2> &vec)const noexcept
        -> std::enable_if_t<Length == 3 && Length2 == 3,Vector<Type,3>> {
            return Vector<Type,3>{
                    (*this)[1] * vec[2] - vec[1] * (*this)[2],
                    (*this)[2] * vec[0] - vec[2] * (*this)[0],
                    (*this)[0] * vec[1] - vec[0] * (*this)[1]
            };
        }


        Type length()const noexcept{
            Type len = 0;
            for(auto itr = this->cbegin();itr != this->cend();++itr){
                len += *itr * *itr;
            }
            return std::sqrt(len);
        }

        Type length2()const noexcept{
            Type len = 0;
            for(auto itr = this->cbegin();itr != this->cend();++itr){
                len += *itr * *itr;
            }
            return len;
        }

        Vector normalize()const noexcept{
            return Vector(this->operator/(length()));
        }

        template <class Type2 = Type,size_t Length2 = Length>
        auto translate()
        -> std::enable_if_t<Length == 3 && Length2 == 3,Matrix<Type,4,4>>{
            return Matrix<Type,4,4>{
                    1,0,0,(*this)[0],
                    0,1,0,(*this)[1],
                    0,0,1,(*this)[2],
                    0,0,0,1
            };
        }

        template <class Type2 = Type,size_t Length2 = Length>
        auto scale()
        -> std::enable_if_t<Length == 3 && Length2 == 3,Matrix<Type,4,4>>{
            return Matrix<Type,4,4>{
                    (*this)[0],0         ,0         ,0,
                    0         ,(*this)[1],0         ,0,
                    0         ,0         ,(*this)[2],0,
                    0         ,0         ,0         ,1
            };
        }

        template <class Type2 = Type,size_t Length2 = Length>
        auto rotate(Type angle)
        -> std::enable_if_t<Length == 3 && Length2 == 3,Matrix<Type,4,4>>{
            auto tmp = normalize();
            auto u = tmp[0];
            auto v = tmp[1];
            auto w = tmp[2];
            //todo:need more tests
            return Matrix<Type2,4,4>{
                    u*u+(1-u*u)*cos(angle)         ,u*v*(1-cos(angle))-w*sin(angle),u*w*(1-cos(angle))+v*sin(angle),0,
                    u*v*(1-cos(angle))+w*sin(angle),v*v+(1-v*v)*cos(angle)         ,v*w*(1-cos(angle))-u*sin(angle),0,
                    u*w*(1-cos(angle))-v*sin(angle),v*w*(1-cos(angle))+u*sin(angle),         w*w+(1-w*w)*cos(angle),0,
                    0                              ,0                              ,0                              ,1
            };
        }
    };

    using Vector2f = Vector<float,2>;
    using Vector3f = Vector<float,3>;
    using Vector4f = Vector<float,4>;

    using Vector2d = Vector<double,2>;
    using Vector3d = Vector<double,3>;
    using Vector4d = Vector<double,4>;

    using Vector2i = Vector<int,2>;
    using Vector3i = Vector<int,3>;
    using Vector4i = Vector<int,4>;

    using Vector2ui = Vector<unsigned int,2>;
    using Vector3ui = Vector<unsigned int,3>;
    using Vector4ui = Vector<unsigned int,4>;


}

#endif
