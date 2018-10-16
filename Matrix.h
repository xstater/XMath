#ifndef _XMATH_MATRIX_H_
#define _XMATH_MATRIX_H_

#include <array>
#include <ostream>
#include <initializer_list>
#include <exception>
#include "Vector.h"

namespace xmath{

    class matrix_singular:public std::exception{
    public:
        matrix_singular() = default;
        ~matrix_singular() = default;

        const char *what()const noexcept{
            return "Matrix is NOT invertible";
        }
    };

    template <class Type>
    constexpr Type _det(Type a,Type b,
                         Type c,Type d)noexcept{
        return a * d - b * c;
    }
    template <class Type>
    constexpr Type _det(Type m0,Type m1,Type m2,
                         Type m3,Type m4,Type m5,
                         Type m6,Type m7,Type m8)noexcept{
        return m0 * m4 * m8 + m1 * m5 * m6 + m2 * m3 * m7 - m6 * m4 * m2 - m7 * m5 * m0 - m8 * m3 * m1;
    }

    template <class Type>
    class Matrix2d{
    public:
        Matrix2d()
                :m_mat{1,0,
                       0,1}{}

        Matrix2d(const Type *ptr)
                :m_mat{ptr[0],ptr[1],
                       ptr[2],ptr[3]}{}

        Matrix2d(const std::initializer_list<Type> &ilist)
                :m_mat{ilist.begin()[0],ilist.begin()[1],
                       ilist.begin()[2],ilist.begin()[3]}{}

        Matrix2d(const Matrix2d<Type> &) = default;
        Matrix2d(Matrix2d<Type> &&) = default;

        template <class Type2>
        Matrix2d(const Matrix2d<Type2> &mat)
                :m_mat{mat[0],mat[1],
                       mat[2],mat[3]}{}

        ~Matrix2d() = default;

        Matrix2d<Type> &operator=(const Matrix2d<Type> &) = default;
        Matrix2d<Type> &operator=(Matrix2d<Type> &&) = default;

        Type &operator[](int index)noexcept{
            return m_mat[index];
        }
        const Type &operator[](int index)const noexcept{
            return m_mat[index];
        }

        Type &operator()(int i,int j)noexcept{
            return m_mat[i * 2 + j];
        }
        const Type &operator()(int i,int j)const noexcept{
            return m_mat[i * 2 + j];
        }

        operator Type*()noexcept{
            return m_mat.data();
        }
        operator const Type*()const noexcept{
            return m_mat.data();
        }

        void identity()noexcept{
            m_mat = std::array<Type,4>{
                    1,0,
                    0,1
            };
        }

        Matrix2d<Type> operator+(const Matrix2d<Type> &mat) const noexcept{
            return Matrix2d<Type> {
                    m_mat[0] + mat[0],m_mat[1] + mat[1],
                    m_mat[2] + mat[2],m_mat[3] + mat[3]
            };
        }
        Matrix2d<Type> operator-(const Matrix2d<Type> &mat) const noexcept{
            return Matrix2d<Type> {
                    m_mat[0] - mat[0],m_mat[1] - mat[1],
                    m_mat[2] - mat[2],m_mat[3] - mat[3]
            };
        }

        Matrix2d<Type> operator+(Type t) const noexcept{
            return Matrix2d<Type> {
                    m_mat[0] + t,m_mat[1] + t,
                    m_mat[2] + t,m_mat[3] + t
            };
        }
        Matrix2d<Type> operator-(Type t) const noexcept{
            return Matrix2d<Type> {
                    m_mat[0] - t,m_mat[1] - t,
                    m_mat[2] - t,m_mat[3] - t
            };
        }
        Matrix2d<Type> operator*(Type t) const noexcept{
            return Matrix2d<Type> {
                    m_mat[0] * t,m_mat[1] * t,
                    m_mat[2] * t,m_mat[3] * t
            };
        }
        Matrix2d<Type> operator/(Type t) const noexcept{
            return Matrix2d<Type> {
                    m_mat[0] / t,m_mat[1] / t,
                    m_mat[2] / t,m_mat[3] / t
            };
        }

        Vector2d<Type> operator*(const Vector2d<Type> &vec)const noexcept{
            return Vector2d<Type>(
                    vec[0] * m_mat[0] + vec[1] * m_mat[1],
                    vec[0] * m_mat[2] + vec[1] * m_mat[3]);
        }

        Matrix2d<Type> operator*(const Matrix2d<Type> &mat)const noexcept{
            return Matrix2d<Type>{
                    m_mat[0] * mat[0] + m_mat[1] * mat[2],m_mat[0] * mat[1] + m_mat[1] * mat[3],
                    m_mat[2] * mat[0] + m_mat[3] * mat[2],m_mat[2] * mat[1] + m_mat[3] * mat[3]
            };
        }

        Type det()const noexcept{
            return m_mat[0] * m_mat[3] - m_mat[1] * m_mat[2];
        }

        Matrix2d<Type> transpose()noexcept{
            return Matrix2d<Type>{
                    m_mat[0],m_mat[2],
                    m_mat[1],m_mat[3],
            };
        }

        friend std::ostream &operator<<(std::ostream &os,const Matrix2d<Type> &mat){
            return os<<mat[0]<<' '<<mat[1]<<'\n'<<mat[2]<<' '<<mat[3];
        }

    protected:
    private:
        std::array<Type,4> m_mat;
    };

    template <class Type>
    class Matrix3d{
    public:
        Matrix3d()
            :m_mat{1,0,0,
                   0,1,0,
                   0,0,1}{}

        Matrix3d(const Type *ptr)
            :m_mat{ptr[0],ptr[1],ptr[2],
                   ptr[3],ptr[4],ptr[5],
                   ptr[6],ptr[7],ptr[8]}{}

        Matrix3d(const std::initializer_list<Type> &ilist)
            :m_mat{ilist.begin()[0],ilist.begin()[1],ilist.begin()[2],
                   ilist.begin()[3],ilist.begin()[4],ilist.begin()[5],
                   ilist.begin()[6],ilist.begin()[7],ilist.begin()[8]}{}

        Matrix3d(const Matrix3d<Type> &) = default;
        Matrix3d(Matrix3d<Type> &&) = default;

        template <class Type2>
        Matrix3d(const Matrix3d<Type2> &mat)
            :m_mat{mat[0],mat[1],mat[2],
                   mat[3],mat[4],mat[5],
                   mat[6],mat[7],mat[8]}{}

        ~Matrix3d() = default;

        Matrix3d<Type> &operator=(const Matrix3d<Type> &) = default;
        Matrix3d<Type> &operator=(Matrix3d<Type> &&) = default;

        Type &operator[](int index)noexcept{
            return m_mat[index];
        }
        const Type &operator[](int index)const noexcept{
            return m_mat[index];
        }

        Type &operator()(int i,int j)noexcept{
            return m_mat[i * 3 + j];
        }
        const Type &operator()(int i,int j)const noexcept{
            return m_mat[i * 3 + j];
        }

        operator Type*()noexcept{
            return m_mat.data();
        }
        operator const Type*()const noexcept{
            return m_mat.data();
        }

        void identity()noexcept{
            m_mat = std::array<Type,9>{
                    1,0,0,
                    0,1,0,
                    0,0,1
            };
        }

        Matrix3d<Type> operator+(const Matrix3d<Type> &mat) const noexcept{
            return Matrix3d<Type> {
                m_mat[0] + mat[0],m_mat[1] + mat[1],m_mat[2] + mat[2],
                m_mat[3] + mat[3],m_mat[4] + mat[4],m_mat[5] + mat[5],
                m_mat[6] + mat[6],m_mat[7] + mat[7],m_mat[8] + mat[8]};
        }
        Matrix3d<Type> operator-(const Matrix3d<Type> &mat) const noexcept{
            return Matrix3d<Type> {
                    m_mat[0] - mat[0],m_mat[1] - mat[1],m_mat[2] - mat[2],
                    m_mat[3] - mat[3],m_mat[4] - mat[4],m_mat[5] - mat[5],
                    m_mat[6] - mat[6],m_mat[7] - mat[7],m_mat[8] - mat[8]};
        }

        Matrix3d<Type> operator+(Type t) const noexcept{
            return Matrix3d<Type> {
                    m_mat[0] + t,m_mat[1] + t,m_mat[2] + t,
                    m_mat[3] + t,m_mat[4] + t,m_mat[5] + t,
                    m_mat[6] + t,m_mat[7] + t,m_mat[8] + t};
        }
        Matrix3d<Type> operator-(Type t) const noexcept{
            return Matrix3d<Type> {
                    m_mat[0] - t,m_mat[1] - t,m_mat[2] - t,
                    m_mat[3] - t,m_mat[4] - t,m_mat[5] - t,
                    m_mat[6] - t,m_mat[7] - t,m_mat[8] - t};
        }
        Matrix3d<Type> operator*(Type t) const noexcept{
            return Matrix3d<Type> {
                    m_mat[0] * t,m_mat[1] * t,m_mat[2] * t,
                    m_mat[3] * t,m_mat[4] * t,m_mat[5] * t,
                    m_mat[6] * t,m_mat[7] * t,m_mat[8] * t};
        }
        Matrix3d<Type> operator/(Type t) const noexcept{
            return Matrix3d<Type> {
                    m_mat[0] / t,m_mat[1] / t,m_mat[2] / t,
                    m_mat[3] / t,m_mat[4] / t,m_mat[5] / t,
                    m_mat[6] / t,m_mat[7] / t,m_mat[8] / t};
        }

        Vector3d<Type> operator*(const Vector3d<Type> &vec)const noexcept{
            return Vector3d<Type>(
                    vec[0] * m_mat[0] + vec[1] * m_mat[1] + vec[2] * m_mat[2],
                    vec[0] * m_mat[3] + vec[1] * m_mat[4] + vec[2] * m_mat[5],
                    vec[0] * m_mat[6] + vec[1] * m_mat[7] + vec[2] * m_mat[8]);
        }

        Matrix3d<Type> operator*(const Matrix3d<Type> &mat)const noexcept{
            return Matrix3d<Type>{
                m_mat[0] * mat[0] + m_mat[1] * mat[3] + m_mat[2] * mat[6], m_mat[0] * mat[1] + m_mat[1] * mat[4] + m_mat[2] * mat[7], m_mat[0] * mat[2] + m_mat[1] * mat[5] + m_mat[2] * mat[8],
                m_mat[3] * mat[0] + m_mat[4] * mat[3] + m_mat[5] * mat[6], m_mat[3] * mat[1] + m_mat[4] * mat[4] + m_mat[5] * mat[7], m_mat[3] * mat[2] + m_mat[4] * mat[5] + m_mat[5] * mat[8],
                m_mat[6] * mat[0] + m_mat[7] * mat[3] + m_mat[8] * mat[6], m_mat[6] * mat[1] + m_mat[7] * mat[4] + m_mat[8] * mat[7], m_mat[6] * mat[2] + m_mat[7] * mat[5] + m_mat[8] * mat[8]
            };
        }

        Type det()const noexcept{
            return m_mat[0] * m_mat[4] * m_mat[8] + m_mat[1] * m_mat[5] * m_mat[6] + m_mat[2] * m_mat[3] * m_mat[7]
                  - m_mat[6] * m_mat[4] * m_mat[2] - m_mat[7] * m_mat[5] * m_mat[0] - m_mat[8] * m_mat[3] * m_mat[1];
        }

        Matrix3d<Type> transpose()noexcept{
            return Matrix3d<Type>{
                m_mat[0],m_mat[3],m_mat[6],
                m_mat[1],m_mat[4],m_mat[7],
                m_mat[2],m_mat[5],m_mat[8]
            };
        }
        Matrix3d<Type> inverse(){
            Type d = det();
            if(float_equal(d,0.0))
                throw matrix_singular();
            auto mt = transpose();
            auto adjm = Matrix3d<Type>{
                _det(mt[4],mt[5],mt[7],mt[8]),-_det(mt[3],mt[5],mt[6],mt[8]), _det(mt[3],mt[4],mt[6],mt[7]),
               -_det(mt[1],mt[2],mt[7],mt[8]), _det(mt[0],mt[2],mt[6],mt[8]),-_det(mt[0],mt[1],mt[6],mt[7]),
                _det(mt[1],mt[2],mt[4],mt[5]),-_det(mt[0],mt[2],mt[3],mt[5]), _det(mt[0],mt[1],mt[3],mt[4])
            };

            return adjm * (1.0 / d);
        }

        friend std::ostream &operator<<(std::ostream &os,const Matrix3d<Type> &mat){
            return os<<mat[0]<<' '<<mat[1]<<' '<<mat[2]<<'\n'<<mat[3]<<' '<<mat[4]<<' '<<mat[5]<<'\n'<<mat[6]<<' '<<mat[7]<<' '<<mat[8];
        }

    protected:
    private:
        std::array<Type,9> m_mat;
    };




    template <class Type>
    class Matrix4d{
    public:
        Matrix4d()
                :m_mat{1,0,0,0,
                       0,1,0,0,
                       0,0,1,0,
                       0,0,0,1}{}

        Matrix4d(const Type *ptr)
                :m_mat{ptr[0x0],ptr[0x1],ptr[0x2],ptr[0x3],
                       ptr[0x4],ptr[0x5],ptr[0x6],ptr[0x7],
                       ptr[0x8],ptr[0x9],ptr[0xA],ptr[0xB],
                       ptr[0xC],ptr[0xD],ptr[0xE],ptr[0xF]}{}

        Matrix4d(const std::initializer_list<Type> &ilist)
                :m_mat{ilist.begin()[0x0],ilist.begin()[0x1],ilist.begin()[0x2],ilist.begin()[0x3],
                       ilist.begin()[0x4],ilist.begin()[0x5],ilist.begin()[0x6],ilist.begin()[0x7],
                       ilist.begin()[0x8],ilist.begin()[0x9],ilist.begin()[0xA],ilist.begin()[0xB],
                       ilist.begin()[0xC],ilist.begin()[0xD],ilist.begin()[0xE],ilist.begin()[0xF]}{}

        Matrix4d(const Matrix4d<Type> &) = default;
        Matrix4d(Matrix4d<Type> &&) = default;

        template <class Type2>
        Matrix4d(const Matrix4d<Type2> &mat)
                :m_mat{mat[0x0],mat[0x1],mat[0x2],mat[0x3],
                       mat[0x4],mat[0x5],mat[0x6],mat[0x7],
                       mat[0x8],mat[0x9],mat[0xA],mat[0xB],
                       mat[0xC],mat[0xD],mat[0xE],mat[0xF]}{}

        ~Matrix4d() = default;

        Matrix4d<Type> &operator=(const Matrix4d<Type> &) = default;
        Matrix4d<Type> &operator=(Matrix4d<Type> &&) = default;

        Type &operator[](int index)noexcept{
            return m_mat[index];
        }
        const Type &operator[](int index)const noexcept{
            return m_mat[index];
        }

        Type &operator()(int i,int j)noexcept{
            return m_mat[i * 4 + j];
        }
        const Type &operator()(int i,int j)const noexcept{
            return m_mat[i * 4 + j];
        }

        operator Type*()noexcept{
            return m_mat.data();
        }
        operator const Type*()const noexcept{
            return m_mat.data();
        }

        void identity()noexcept{
            m_mat = std::array<Type,16> {
                1,0,0,0,
                0,1,0,0,
                0,0,1,0,
                0,0,0,1
            };
        }

        Matrix4d<Type> operator+(const Matrix4d<Type> &mat) const noexcept{
            return Matrix4d<Type> {
                    m_mat[0x0] + mat[0x0],m_mat[0x1] + mat[0x1],m_mat[0x2] + mat[0x2],m_mat[0x3] + mat[0x3],
                    m_mat[0x4] + mat[0x4],m_mat[0x5] + mat[0x5],m_mat[0x6] + mat[0x6],m_mat[0x7] + mat[0x7],
                    m_mat[0x8] + mat[0x8],m_mat[0x9] + mat[0x9],m_mat[0xA] + mat[0xA],m_mat[0xB] + mat[0xB],
                    m_mat[0xC] + mat[0xC],m_mat[0xD] + mat[0xD],m_mat[0xE] + mat[0xE],m_mat[0xF] + mat[0xF]};
        }
        Matrix4d<Type> operator-(const Matrix4d<Type> &mat) const noexcept{
            return Matrix4d<Type> {
                    m_mat[0x0] - mat[0x0],m_mat[0x1] - mat[0x1],m_mat[0x2] - mat[0x2],m_mat[0x3] - mat[0x3],
                    m_mat[0x4] - mat[0x4],m_mat[0x5] - mat[0x5],m_mat[0x6] - mat[0x6],m_mat[0x7] - mat[0x7],
                    m_mat[0x8] - mat[0x8],m_mat[0x9] - mat[0x9],m_mat[0xA] - mat[0xA],m_mat[0xB] - mat[0xB],
                    m_mat[0xC] - mat[0xC],m_mat[0xD] - mat[0xD],m_mat[0xE] - mat[0xE],m_mat[0xF] - mat[0xF]};
        }

        Matrix4d<Type> operator+(Type t) const noexcept{
            return Matrix4d<Type> {
                    m_mat[0x0] + t,m_mat[0x1] + t,m_mat[0x2] + t,m_mat[0x3] + t,
                    m_mat[0x4] + t,m_mat[0x5] + t,m_mat[0x6] + t,m_mat[0x7] + t,
                    m_mat[0x8] + t,m_mat[0x9] + t,m_mat[0xA] + t,m_mat[0xB] + t,
                    m_mat[0xC] + t,m_mat[0xD] + t,m_mat[0xE] + t,m_mat[0xF] + t};
        }
        Matrix4d<Type> operator-(Type t) const noexcept{
            return Matrix4d<Type> {
                    m_mat[0x0] - t,m_mat[0x1] - t,m_mat[0x2] - t,m_mat[0x3] - t,
                    m_mat[0x4] - t,m_mat[0x5] - t,m_mat[0x6] - t,m_mat[0x7] - t,
                    m_mat[0x8] - t,m_mat[0x9] - t,m_mat[0xA] - t,m_mat[0xB] - t,
                    m_mat[0xC] - t,m_mat[0xD] - t,m_mat[0xE] - t,m_mat[0xF] - t};
        }
        Matrix4d<Type> operator*(Type t) const noexcept{
            return Matrix4d<Type> {
                    m_mat[0x0] * t,m_mat[0x1] * t,m_mat[0x2] * t,m_mat[0x3] * t,
                    m_mat[0x4] * t,m_mat[0x5] * t,m_mat[0x6] * t,m_mat[0x7] * t,
                    m_mat[0x8] * t,m_mat[0x9] * t,m_mat[0xA] * t,m_mat[0xB] * t,
                    m_mat[0xC] * t,m_mat[0xD] * t,m_mat[0xE] * t,m_mat[0xF] * t};
        }
        Matrix4d<Type> operator/(Type t) const noexcept{
            return Matrix4d<Type> {
                    m_mat[0x0] / t,m_mat[0x1] / t,m_mat[0x2] / t,m_mat[0x3] / t,
                    m_mat[0x4] / t,m_mat[0x5] / t,m_mat[0x6] / t,m_mat[0x7] / t,
                    m_mat[0x8] / t,m_mat[0x9] / t,m_mat[0xA] / t,m_mat[0xB] / t,
                    m_mat[0xC] / t,m_mat[0xD] / t,m_mat[0xE] / t,m_mat[0xF] / t};
        }

        Vector4d<Type> operator*(const Vector4d<Type> &vec)const noexcept{
            return Vector4d<Type>(
                    vec[0] * m_mat[0x0] + vec[1] * m_mat[0x1] + vec[2] * m_mat[0x2] + vec[3] * m_mat[0x3],
                    vec[0] * m_mat[0x4] + vec[1] * m_mat[0x5] + vec[2] * m_mat[0x6] + vec[3] * m_mat[0x7],
                    vec[0] * m_mat[0x8] + vec[1] * m_mat[0x9] + vec[2] * m_mat[0xA] + vec[3] * m_mat[0xB],
                    vec[0] * m_mat[0xC] + vec[1] * m_mat[0xD] + vec[2] * m_mat[0xE] + vec[3] * m_mat[0xF]);
        }

        Matrix4d<Type> operator*(const Matrix4d<Type> &mat)const noexcept{
            //0 1 2 3   0 1 2 3
            //4 5 6 7   4 5 6 7
            //8 9 A B   8 9 A B
            //C D E F   C D E F
            return Matrix4d<Type>{
                m_mat[0x0] * mat[0x0] + m_mat[0x1] * mat[0x4] + m_mat[0x2] * mat[0x8] + m_mat[0x3] * mat[0xC],//[0]
                m_mat[0x0] * mat[0x1] + m_mat[0x1] * mat[0x5] + m_mat[0x2] * mat[0x9] + m_mat[0x3] * mat[0xD],//[1]
                m_mat[0x0] * mat[0x2] + m_mat[0x1] * mat[0x6] + m_mat[0x2] * mat[0xA] + m_mat[0x3] * mat[0xE],//[2]
                m_mat[0x0] * mat[0x3] + m_mat[0x1] * mat[0x7] + m_mat[0x2] * mat[0xB] + m_mat[0x3] * mat[0xF],//[3]

                m_mat[0x4] * mat[0x0] + m_mat[0x5] * mat[0x4] + m_mat[0x6] * mat[0x8] + m_mat[0x7] * mat[0xC],//[4]
                m_mat[0x4] * mat[0x1] + m_mat[0x5] * mat[0x5] + m_mat[0x6] * mat[0x9] + m_mat[0x7] * mat[0xD],//[5]
                m_mat[0x4] * mat[0x2] + m_mat[0x5] * mat[0x6] + m_mat[0x6] * mat[0xA] + m_mat[0x7] * mat[0xE],//[6]
                m_mat[0x4] * mat[0x3] + m_mat[0x5] * mat[0x7] + m_mat[0x6] * mat[0xB] + m_mat[0x7] * mat[0xF],//[7]

                m_mat[0x8] * mat[0x0] + m_mat[0x9] * mat[0x4] + m_mat[0xA] * mat[0x8] + m_mat[0xB] * mat[0xC],//[8]
                m_mat[0x8] * mat[0x1] + m_mat[0x9] * mat[0x5] + m_mat[0xA] * mat[0x9] + m_mat[0xB] * mat[0xD],//[9]
                m_mat[0x8] * mat[0x2] + m_mat[0x9] * mat[0x6] + m_mat[0xA] * mat[0xA] + m_mat[0xB] * mat[0xE],//[A]
                m_mat[0x8] * mat[0x3] + m_mat[0x9] * mat[0x7] + m_mat[0xA] * mat[0xB] + m_mat[0xB] * mat[0xF],//[B]

                m_mat[0xC] * mat[0x0] + m_mat[0xD] * mat[0x4] + m_mat[0xE] * mat[0x8] + m_mat[0xF] * mat[0xC],//[C]
                m_mat[0xC] * mat[0x1] + m_mat[0xD] * mat[0x5] + m_mat[0xE] * mat[0x9] + m_mat[0xF] * mat[0xD],//[D]
                m_mat[0xC] * mat[0x2] + m_mat[0xD] * mat[0x6] + m_mat[0xE] * mat[0xA] + m_mat[0xF] * mat[0xE],//[E]
                m_mat[0xC] * mat[0x3] + m_mat[0xD] * mat[0x7] + m_mat[0xE] * mat[0xB] + m_mat[0xF] * mat[0xF] //[F]
            };
        }

        Type det()const noexcept{
            //= a11a22a33a44 - a11a22a34a43 - a11a23a32a44 + a11a23a34a42
            //+ a11a24a32a43 - a11a24a33a42 - a12a21a33a44 + a12a21a34a43
            //+ a12a23a31a44 - a12a23a34a41 - a12a24a31a43 + a12a24a33a41
            //+ a13a21a32a44 - a13a21a34a42 - a13a22a31a44 + a13a22a34a41
            //+ a13a24a31a42 - a13a24a32a41 - a14a21a32a43 + a14a21a33a42
            //+ a14a22a31a43 - a14a22a33a41 - a14a23a31a42 + a14a23a32a41
            // 0 1 2 3  a11 a12 a13 a14
            // 4 5 6 7  a21 a22 a23 a24
            // 8 9 A B  a31 a32 a33 a34
            // C D E F  a41 a42 a43 a44
            return
                m_mat[0x0] * m_mat[0x5] * m_mat[0xA] * m_mat[0xF] - m_mat[0x0] * m_mat[0x5] * m_mat[0xB] * m_mat[0xE] - m_mat[0x0] * m_mat[0x6] * m_mat[0x9] * m_mat[0xF] + m_mat[0x0] * m_mat[0x6] * m_mat[0xB] * m_mat[0xD]
              + m_mat[0x0] * m_mat[0x7] * m_mat[0x9] * m_mat[0xE] - m_mat[0x0] * m_mat[0x7] * m_mat[0xA] * m_mat[0xD] - m_mat[0x1] * m_mat[0x4] * m_mat[0xA] * m_mat[0xF] + m_mat[0x1] * m_mat[0x4] * m_mat[0xB] * m_mat[0xE]
              + m_mat[0x1] * m_mat[0x6] * m_mat[0x8] * m_mat[0xF] - m_mat[0x1] * m_mat[0x6] * m_mat[0xB] * m_mat[0xC] - m_mat[0x1] * m_mat[0x7] * m_mat[0x8] * m_mat[0xE] + m_mat[0x1] * m_mat[0x7] * m_mat[0xA] * m_mat[0xC]
              + m_mat[0x2] * m_mat[0x4] * m_mat[0x9] * m_mat[0xF] - m_mat[0x2] * m_mat[0x4] * m_mat[0xB] * m_mat[0xD] - m_mat[0x2] * m_mat[0x5] * m_mat[0x8] * m_mat[0xF] + m_mat[0x2] * m_mat[0x5] * m_mat[0xB] * m_mat[0xC]
              + m_mat[0x2] * m_mat[0x7] * m_mat[0x8] * m_mat[0xD] - m_mat[0x2] * m_mat[0x7] * m_mat[0x9] * m_mat[0xC] - m_mat[0x3] * m_mat[0x4] * m_mat[0x9] * m_mat[0xE] + m_mat[0x3] * m_mat[0x4] * m_mat[0xA] * m_mat[0xD]
              + m_mat[0x3] * m_mat[0x5] * m_mat[0x8] * m_mat[0xE] - m_mat[0x3] * m_mat[0x5] * m_mat[0xA] * m_mat[0xC] - m_mat[0x3] * m_mat[0x6] * m_mat[0x8] * m_mat[0xD] + m_mat[0x3] * m_mat[0x6] * m_mat[0x9] * m_mat[0xC];
        }

        Matrix4d<Type> transpose()noexcept{
            //0 4 8 C
            //1 5 9 D
            //2 6 A E
            //3 7 B F
            return Matrix4d<Type>{
                m_mat[0x0],m_mat[0x4],m_mat[0x8],m_mat[0xC],
                m_mat[0x1],m_mat[0x5],m_mat[0x9],m_mat[0xD],
                m_mat[0x2],m_mat[0x6],m_mat[0xA],m_mat[0xE],
                m_mat[0x3],m_mat[0x7],m_mat[0xB],m_mat[0xF]
            };
        }
        Matrix4d<Type> inverse(){
            Type d = det();
            if(float_equal(d,0.0f))
                throw matrix_singular();
            auto mt = transpose();
            //+0 -1 +2 -3
            //-4 +5 -6 +7
            //+8 -9 +A -B
            //-C +D -E +F
            auto adjm = Matrix4d<Type>{
                _det(mt[0x5],mt[0x6],mt[0x7], mt[0x9],mt[0xA],mt[0xB], mt[0xD],mt[0xE],mt[0xF]),//0
              - _det(mt[0x4],mt[0x6],mt[0x7], mt[0x8],mt[0xA],mt[0xB], mt[0xC],mt[0xE],mt[0xF]),//1
                _det(mt[0x4],mt[0x5],mt[0x7], mt[0x8],mt[0x9],mt[0xB], mt[0xC],mt[0xD],mt[0xF]),//2
              - _det(mt[0x4],mt[0x5],mt[0x6], mt[0x8],mt[0x9],mt[0xA], mt[0xC],mt[0xD],mt[0xE]),//3

              - _det(mt[0x1],mt[0x2],mt[0x3], mt[0x9],mt[0xA],mt[0xB], mt[0xD],mt[0xE],mt[0xF]),//4
                _det(mt[0x0],mt[0x2],mt[0x3], mt[0x8],mt[0xA],mt[0xB], mt[0xC],mt[0xE],mt[0xF]),//5
              - _det(mt[0x0],mt[0x1],mt[0x3], mt[0x8],mt[0x9],mt[0xB], mt[0xC],mt[0xD],mt[0xF]),//6
                _det(mt[0x0],mt[0x1],mt[0x2], mt[0x8],mt[0x9],mt[0xA], mt[0xC],mt[0xD],mt[0xE]),//7

                _det(mt[0x1],mt[0x2],mt[0x3], mt[0x5],mt[0x6],mt[0x7], mt[0xD],mt[0xE],mt[0xF]),//8
              - _det(mt[0x0],mt[0x2],mt[0x3], mt[0x4],mt[0x6],mt[0x7], mt[0xC],mt[0xE],mt[0xF]),//9
                _det(mt[0x0],mt[0x1],mt[0x3], mt[0x4],mt[0x5],mt[0x7], mt[0xC],mt[0xD],mt[0xF]),//A
              - _det(mt[0x0],mt[0x1],mt[0x2], mt[0x4],mt[0x5],mt[0x6], mt[0xC],mt[0xD],mt[0xE]),//B

              - _det(mt[0x1],mt[0x2],mt[0x3], mt[0x5],mt[0x6],mt[0x7], mt[0x9],mt[0xA],mt[0xB]),//C
                _det(mt[0x0],mt[0x2],mt[0x3], mt[0x4],mt[0x6],mt[0x7], mt[0x8],mt[0xA],mt[0xB]),//D
              - _det(mt[0x0],mt[0x1],mt[0x3], mt[0x4],mt[0x5],mt[0x7], mt[0x8],mt[0x9],mt[0xB]),//E
                _det(mt[0x0],mt[0x1],mt[0x2], mt[0x4],mt[0x5],mt[0x6], mt[0x8],mt[0x9],mt[0xA]) //F
            };

            return adjm * (1.0 / d);
        }

        friend std::ostream &operator<<(std::ostream &os,const Matrix4d<Type> &mat){
            return os<<mat[0x0]<<' '<<mat[0x1]<<' '<<mat[0x2]<<' '<<mat[0x3]<<'\n'
                      <<mat[0x4]<<' '<<mat[0x5]<<' '<<mat[0x6]<<' '<<mat[0x7]<<'\n'
                      <<mat[0x8]<<' '<<mat[0x9]<<' '<<mat[0xA]<<' '<<mat[0xB]<<'\n'
                      <<mat[0xC]<<' '<<mat[0xD]<<' '<<mat[0xE]<<' '<<mat[0xF]<<'\n';
        }

    protected:
    private:
        std::array<Type,16> m_mat;
    };

}

#endif




