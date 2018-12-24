#ifndef _XMATH_MATRIX_H_
#define _XMATH_MATRIX_H_

#include <array>
#include "Vector.h"

namespace xmath{
    template <class Type>
    class Matrix3d{
    public:
        Matrix3d(){
            for(int i = 0; i < 9; i++)
                m_mat[i] = (i % 4) ? 0 : 1;
        }
        Matrix3d(std::initializer_list<Type> list){
            for(int i = 0; i < 9 ;++i)
                m_mat[i] = list.begin()[i];
        }
        Matrix3d(const Type *data){
            for(int i = 0;i < 9;++i){
                m_mat[i] = data[i];
            }
        }
        template<class Type2>
        Matrix3d(const Matrix3d<Type2> &mat){
            for(int i = 0;i < 9;++i)
                m_mat[i] = static_cast<Type>(mat[i]);
        }
        ~Matrix3d() = default;

        void idendity(){
            for(int i = 0; i < 9; i++)
                m_mat[i] = (i % 4) ? 0 : 1;
        };

        Type &operator[](int index)noexcept{
            return m_mat[index];
        }
        const Type &operator[](int index)const noexcept{
            return m_mat[index];
        }

        operator Type*()noexcept{
            return m_mat.data();
        }
        operator const Type*()const noexcept{
            return m_mat.data();
        }

        Type &operator()(int x,int y)noexcept{
            return m_mat[x * 3 + y];
        }
        const Type &operator()(int x,int y)const noexcept{
            return m_mat[x * 3 + y];
        }

        Matrix3d operator+(const Matrix3d &mat)const noexcept{
            Matrix3d ans;
            for(int i = 0;i < 9;++i)
                ans[i] = m_mat[i] + mat[i];
            return ans;
        }
        Matrix3d operator-(const Matrix3d &mat)const noexcept{
            Matrix3d ans;
            for(int i = 0;i < 9;++i)
                ans[i] = m_mat[i] - mat[i];
            return ans;
        }
        Matrix3d operator+(const Type &dat)const noexcept{
            Matrix3d ans;
            for(int i = 0;i < 9;++i)
                ans[i] = m_mat[i] + dat;
            return ans;
        }
        Matrix3d operator-(const Type &dat)const noexcept{
            Matrix3d ans;
            for(int i = 0;i < 9;++i)
                ans[i] = m_mat[i] - dat;
            return ans;
        }
        Matrix3d operator*(const Type &dat)const noexcept{
            Matrix3d ans;
            for(int i = 0;i < 9;++i)
                ans[i] = m_mat[i] * dat;
            return ans;
        }
        Matrix3d operator/(const Type &dat)const noexcept{
            Matrix3d ans;
            for(int i = 0;i < 9;++i)
                ans[i] = m_mat[i] / dat;
            return ans;
        }

        Matrix3d &operator+=(const Matrix3d &mat)noexcept{
            for(int i = 0;i < 9;++i)
                m_mat[i] += mat[i];
            return *this;
        }
        Matrix3d &operator-=(const Matrix3d &mat)noexcept{
            for(int i = 0;i < 9;++i)
                m_mat[i] -= mat[i];
            return *this;
        }
        Matrix3d &operator+=(const Type &dat)noexcept{
            for(int i = 0;i < 9;++i)
                m_mat[i] += dat;
            return *this;
        }
        Matrix3d &operator-=(const Type &dat)noexcept{
            for(int i = 0;i < 9;++i)
                m_mat[i] -= dat;
            return *this;
        }
        Matrix3d &operator*=(const Type &dat)noexcept{
            for(int i = 0;i < 9;++i)
                m_mat[i] *= dat;
            return *this;
        }
        Matrix3d &operator/=(const Type &dat)noexcept{
            for(int i = 0;i < 9;++i)
                m_mat[i] /= dat;
            return *this;
        }

        Vector3d<Type> operator*(const Vector3d<Type> &rhs)const noexcept{
            return Vector3d<Type>(m_mat[0] * rhs.x + m_mat[3] * rhs.y + m_mat[6] * rhs.z,
                                  m_mat[1] * rhs.x + m_mat[4] * rhs.y + m_mat[7] * rhs.z,
                                  m_mat[2] * rhs.x + m_mat[5] * rhs.y + m_mat[8] * rhs.z);
        }
        Matrix3d operator*(const Matrix3d &rhs)const noexcept{
            Matrix3d mat;
            for (int i = 0; i < 3; i++){
                for (int j = 0; j < 3; j++){
                    Type sum = 0;
                    for (int k = 0; k < 3; k++)
                        sum += rhs(i,k) * (*this)(k,j);
                    mat(i,j) = sum;
                }
            }
            return mat;
        }

        Matrix3d transpose()noexcept{
            Matrix3d mat;
            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++)
                    mat(i, j) = (*this)(j, i);
            return mat;
        }

        Type det()const noexcept{
            return (*this)(0,0) * (*this)(1,1) * (*this)(2,2)
                  +(*this)(0,1) * (*this)(1,2) * (*this)(2,0)
                  +(*this)(0,2) * (*this)(1,0) * (*this)(2,1)
                  -(*this)(0,0) * (*this)(1,2) * (*this)(2,1)
                  -(*this)(0,1) * (*this)(1,0) * (*this)(2,2)
                  -(*this)(0,2) * (*this)(1,1) * (*this)(2,0);
        }
        Matrix3d inverse()const noexcept{
            Matrix3d mat;
            mat(0,0) = (*this)(1,1) * (*this)(2,2) - (*this)(2,1) * (*this)(1,2);
            mat(0,1) = (*this)(2,1) * (*this)(0,2) - (*this)(0,1) * (*this)(2,2);
            mat(0,2) = (*this)(0,1) * (*this)(1,2) - (*this)(1,1) * (*this)(0,2);
            mat(1,0) = (*this)(2,0) * (*this)(1,2) - (*this)(1,0) * (*this)(2,2);
            mat(1,1) = (*this)(0,0) * (*this)(2,2) - (*this)(2,0) * (*this)(0,2);
            mat(1,2) = (*this)(1,0) * (*this)(0,2) - (*this)(0,0) * (*this)(1,2);
            mat(2,0) = (*this)(1,0) * (*this)(2,1) - (*this)(2,0) * (*this)(1,1);
            mat(2,1) = (*this)(2,0) * (*this)(0,1) - (*this)(0,0) * (*this)(2,1);
            mat(2,2) = (*this)(0,0) * (*this)(1,1) - (*this)(1,0) * (*this)(0,1);
            return mat * (static_cast<Type>(1.0) / det());
        }

        friend std::ostream &operator<<(std::ostream &os,const Matrix3d<Type> &mat){
            os<<"["<<mat[0]<<','<<mat[1]<<','<<mat[2]<<']'<<'\n';
            os<<"["<<mat[3]<<','<<mat[4]<<','<<mat[5]<<']'<<'\n';
            os<<"["<<mat[6]<<','<<mat[7]<<','<<mat[8]<<']'<<'\n';
            return os;
        }
    protected:
    private:
        std::array<Type,9> m_mat;
    };

    template <class Type>
    class Matrix4d{
    public:
        Matrix4d(){
            for(int i = 0; i < 16; i++)
                m_mat[i] = (i % 5) ? 0 : 1;
        }
        Matrix4d(std::initializer_list<Type> list){
            for(int i = 0; i < 16 ;++i)
                m_mat[i] = list.begin()[i];
        }
        Matrix4d(const Type *data){
            for(int i = 0;i < 16;++i){
                m_mat[i] = data[i];
            }
        }
        template<class Type2>
        Matrix4d(const Matrix4d<Type2> &mat){
            for(int i = 0;i < 16;++i)
                m_mat[i] = static_cast<Type>(mat[i]);
        }
        ~Matrix4d() = default;

        void idendity(){
            for(int i = 0; i < 16; i++)
                m_mat[i] = (i % 5) ? 0 : 1;
        };

        Type &operator[](int index)noexcept{
            return m_mat[index];
        }
        const Type &operator[](int index)const noexcept{
            return m_mat[index];
        }

        operator Type*()noexcept{
            return m_mat.data();
        }
        operator const Type*()const noexcept{
            return m_mat.data();
        }

        Type &operator()(int x,int y)noexcept{
            return m_mat[x * 4 + y];
        }
        const Type &operator()(int x,int y)const noexcept{
            return m_mat[x * 4 + y];
        }

        Matrix4d operator+(const Matrix4d &mat)const noexcept{
            Matrix4d ans;
            for(int i = 0;i < 16;++i)
                ans[i] = m_mat[i] + mat[i];
            return ans;
        }
        Matrix4d operator-(const Matrix4d &mat)const noexcept{
            Matrix4d ans;
            for(int i = 0;i < 16;++i)
                ans[i] = m_mat[i] - mat[i];
            return ans;
        }
        Matrix4d operator+(const Type &dat)const noexcept{
            Matrix4d ans;
            for(int i = 0;i < 16;++i)
                ans[i] = m_mat[i] + dat;
            return ans;
        }
        Matrix4d operator-(const Type &dat)const noexcept{
            Matrix4d ans;
            for(int i = 0;i < 16;++i)
                ans[i] = m_mat[i] - dat;
            return ans;
        }
        Matrix4d operator*(const Type &dat)const noexcept{
            Matrix4d ans;
            for(int i = 0;i < 16;++i)
                ans[i] = m_mat[i] * dat;
            return ans;
        }
        Matrix4d operator/(const Type &dat)const noexcept{
            Matrix4d ans;
            for(int i = 0;i < 16;++i)
                ans[i] = m_mat[i] / dat;
            return ans;
        }

        Matrix4d &operator+=(const Matrix4d &mat)noexcept{
            for(int i = 0;i < 16;++i)
                m_mat[i] += mat[i];
            return *this;
        }
        Matrix4d &operator-=(const Matrix4d &mat)noexcept{
            for(int i = 0;i < 16;++i)
                m_mat[i] -= mat[i];
            return *this;
        }
        Matrix4d &operator+=(const Type &dat)noexcept{
            for(int i = 0;i < 16;++i)
                m_mat[i] += dat;
            return *this;
        }
        Matrix4d &operator-=(const Type &dat)noexcept{
            for(int i = 0;i < 16;++i)
                m_mat[i] -= dat;
            return *this;
        }
        Matrix4d &operator*=(const Type &dat)noexcept{
            for(int i = 0;i < 16;++i)
                m_mat[i] *= dat;
            return *this;
        }
        Matrix4d &operator/=(const Type &dat)noexcept{
            for(int i = 0;i < 16;++i)
                m_mat[i] /= dat;
            return *this;
        }

        Vector4d<Type> operator*(const Vector4d<Type> &rhs)const noexcept{
            return Vector4d<Type>(m_mat[0] * rhs.x + m_mat[4] * rhs.y + m_mat[8] * rhs.z  + m_mat[12] * rhs.w,
                                  m_mat[1] * rhs.x + m_mat[5] * rhs.y + m_mat[9] * rhs.z  + m_mat[13] * rhs.w,
                                  m_mat[2] * rhs.x + m_mat[6] * rhs.y + m_mat[10] * rhs.z + m_mat[14] * rhs.w,
                                  m_mat[3] * rhs.x + m_mat[7] * rhs.y + m_mat[11] * rhs.z + m_mat[15] * rhs.w);
        }
        Matrix4d operator*(const Matrix4d &rhs)const noexcept{
            Matrix4d mat;
            for (int i = 0; i < 4; i++){
                for (int j = 0; j < 4; j++){
                    Type sum = 0;
                    for (int k = 0; k < 4; k++)
                        sum += rhs(i,k) * (*this)(k,j);
                    mat(i,j) = sum;
                }
            }
            return mat;
        }

        Matrix4d transpose()noexcept{
            Matrix4d mat;
            for (int i = 0; i < 4; i++)
                for (int j = 0; j < 4; j++)
                    mat(i, j) = (*this)(j, i);
            return mat;
        }

        Type det()const noexcept{
            return
                 (*this)(3,0) * (*this)(2,1) * (*this)(1,2) * (*this)(0,3)
                -(*this)(2,0) * (*this)(3,1) * (*this)(1,2) * (*this)(0,3)
                -(*this)(3,0) * (*this)(1,1) * (*this)(2,2) * (*this)(0,3)
                +(*this)(1,0) * (*this)(3,1) * (*this)(2,2) * (*this)(0,3)
                
                +(*this)(2,0) * (*this)(1,1) * (*this)(3,2) * (*this)(0,3)
                -(*this)(1,0) * (*this)(2,1) * (*this)(3,2) * (*this)(0,3)
                -(*this)(3,0) * (*this)(2,1) * (*this)(0,2) * (*this)(1,3)
                +(*this)(2,0) * (*this)(3,1) * (*this)(0,2) * (*this)(1,3)

                +(*this)(3,0) * (*this)(0,1) * (*this)(2,2) * (*this)(1,3)
                -(*this)(0,0) * (*this)(3,1) * (*this)(2,2) * (*this)(1,3)
                -(*this)(2,0) * (*this)(0,1) * (*this)(3,2) * (*this)(1,3)
                +(*this)(0,0) * (*this)(2,1) * (*this)(3,2) * (*this)(1,3)
                
                +(*this)(3,0) * (*this)(1,1) * (*this)(0,2) * (*this)(2,3)
                -(*this)(1,0) * (*this)(3,1) * (*this)(0,2) * (*this)(2,3)
                -(*this)(3,0) * (*this)(0,1) * (*this)(1,2) * (*this)(2,3)
                +(*this)(0,0) * (*this)(3,1) * (*this)(1,2) * (*this)(2,3)

                +(*this)(1,0) * (*this)(0,1) * (*this)(3,2) * (*this)(2,3)
                -(*this)(0,0) * (*this)(1,1) * (*this)(3,2) * (*this)(2,3)
                -(*this)(2,0) * (*this)(1,1) * (*this)(0,2) * (*this)(3,3)
                +(*this)(1,0) * (*this)(2,1) * (*this)(0,2) * (*this)(3,3)

                +(*this)(2,0) * (*this)(0,1) * (*this)(1,2) * (*this)(3,3)
                -(*this)(0,0) * (*this)(2,1) * (*this)(1,2) * (*this)(3,3)
                -(*this)(1,0) * (*this)(0,1) * (*this)(2,2) * (*this)(3,3)
                +(*this)(0,0) * (*this)(1,1) * (*this)(2,2) * (*this)(3,3);
        }
        Matrix4d inverse()const noexcept{
            Matrix4d<Type> mat;

            mat(0,0) =  +(*this)(2,1) * (*this)(3,2) * (*this)(1,3) - (*this)(3,1) * (*this)(2,2) * (*this)(1,3) + (*this)(3,1) * (*this)(1,2) * (*this)(2,3)
                        -(*this)(1,1) * (*this)(3,2) * (*this)(2,3) - (*this)(2,1) * (*this)(1,2) * (*this)(3,3) + (*this)(1,1) * (*this)(2,2) * (*this)(3,3);

            mat(1,0) =  +(*this)(3,0) * (*this)(2,2) * (*this)(1,3) - (*this)(2,0) * (*this)(3,2) * (*this)(1,3) - (*this)(3,0) * (*this)(1,2) * (*this)(2,3)
                        +(*this)(1,0) * (*this)(3,2) * (*this)(2,3) + (*this)(2,0) * (*this)(1,2) * (*this)(3,3) - (*this)(1,0) * (*this)(2,2) * (*this)(3,3);

            mat(2,0) =  +(*this)(2,0) * (*this)(3,1) * (*this)(1,3) - (*this)(3,0) * (*this)(2,1) * (*this)(1,3) + (*this)(3,0) * (*this)(1,1) * (*this)(2,3)
                        -(*this)(1,0) * (*this)(3,1) * (*this)(2,3) - (*this)(2,0) * (*this)(1,1) * (*this)(3,3) + (*this)(1,0) * (*this)(2,1) * (*this)(3,3);

            mat(3,0) =  +(*this)(3,0) * (*this)(2,1) * (*this)(1,2) - (*this)(2,0) * (*this)(3,1) * (*this)(1,2) - (*this)(3,0) * (*this)(1,1) * (*this)(2,2)
                        +(*this)(1,0) * (*this)(3,1) * (*this)(2,2) + (*this)(2,0) * (*this)(1,1) * (*this)(3,2) - (*this)(1,0) * (*this)(2,1) * (*this)(3,2);

            mat(0,1) =  +(*this)(3,1) * (*this)(2,2) * (*this)(0,3) - (*this)(2,1) * (*this)(3,2) * (*this)(0,3) - (*this)(3,1) * (*this)(0,2) * (*this)(2,3)
                        +(*this)(0,1) * (*this)(3,2) * (*this)(2,3) + (*this)(2,1) * (*this)(0,2) * (*this)(3,3) - (*this)(0,1) * (*this)(2,2) * (*this)(3,3);

            mat(1,1) =  +(*this)(2,0) * (*this)(3,2) * (*this)(0,3) - (*this)(3,0) * (*this)(2,2) * (*this)(0,3) + (*this)(3,0) * (*this)(0,2) * (*this)(2,3)
                        -(*this)(0,0) * (*this)(3,2) * (*this)(2,3) - (*this)(2,0) * (*this)(0,2) * (*this)(3,3) + (*this)(0,0) * (*this)(2,2) * (*this)(3,3);

            mat(2,1) =  +(*this)(3,0) * (*this)(2,1) * (*this)(0,3) - (*this)(2,0) * (*this)(3,1) * (*this)(0,3) - (*this)(3,0) * (*this)(0,1) * (*this)(2,3)
                        +(*this)(0,0) * (*this)(3,1) * (*this)(2,3) + (*this)(2,0) * (*this)(0,1) * (*this)(3,3) - (*this)(0,0) * (*this)(2,1) * (*this)(3,3);

            mat(3,1) =  +(*this)(2,0) * (*this)(3,1) * (*this)(0,2) - (*this)(3,0) * (*this)(2,1) * (*this)(0,2) + (*this)(3,0) * (*this)(0,1) * (*this)(2,2)
                        -(*this)(0,0) * (*this)(3,1) * (*this)(2,2) - (*this)(2,0) * (*this)(0,1) * (*this)(3,2) + (*this)(0,0) * (*this)(2,1) * (*this)(3,2);

            mat(0,2) =  +(*this)(1,1) * (*this)(3,2) * (*this)(0,3) - (*this)(3,1) * (*this)(1,2) * (*this)(0,3) + (*this)(3,1) * (*this)(0,2) * (*this)(1,3)
                        -(*this)(0,1) * (*this)(3,2) * (*this)(1,3) - (*this)(1,1) * (*this)(0,2) * (*this)(3,3) + (*this)(0,1) * (*this)(1,2) * (*this)(3,3);

            mat(1,2) =  +(*this)(3,0) * (*this)(1,2) * (*this)(0,3) - (*this)(1,0) * (*this)(3,2) * (*this)(0,3) - (*this)(3,0) * (*this)(0,2) * (*this)(1,3)
                        +(*this)(0,0) * (*this)(3,2) * (*this)(1,3) + (*this)(1,0) * (*this)(0,2) * (*this)(3,3) - (*this)(0,0) * (*this)(1,2) * (*this)(3,3);

            mat(2,2) =  +(*this)(1,0) * (*this)(3,1) * (*this)(0,3) - (*this)(3,0) * (*this)(1,1) * (*this)(0,3) + (*this)(3,0) * (*this)(0,1) * (*this)(1,3)
                        -(*this)(0,0) * (*this)(3,1) * (*this)(1,3) - (*this)(1,0) * (*this)(0,1) * (*this)(3,3) + (*this)(0,0) * (*this)(1,1) * (*this)(3,3);

            mat(3,2) =  +(*this)(3,0) * (*this)(1,1) * (*this)(0,2) - (*this)(1,0) * (*this)(3,1) * (*this)(0,2) - (*this)(3,0) * (*this)(0,1) * (*this)(1,2)
                        +(*this)(0,0) * (*this)(3,1) * (*this)(1,2) + (*this)(1,0) * (*this)(0,1) * (*this)(3,2) - (*this)(0,0) * (*this)(1,1) * (*this)(3,2);

            mat(0,3) =  +(*this)(2,1) * (*this)(1,2) * (*this)(0,3) - (*this)(1,1) * (*this)(2,2) * (*this)(0,3) - (*this)(2,1) * (*this)(0,2) * (*this)(1,3)
                        +(*this)(0,1) * (*this)(2,2) * (*this)(1,3) + (*this)(1,1) * (*this)(0,2) * (*this)(2,3) - (*this)(0,1) * (*this)(1,2) * (*this)(2,3);

            mat(1,3) =  +(*this)(1,0) * (*this)(2,2) * (*this)(0,3) - (*this)(2,0) * (*this)(1,2) * (*this)(0,3) + (*this)(2,0) * (*this)(0,2) * (*this)(1,3)
                        -(*this)(0,0) * (*this)(2,2) * (*this)(1,3) - (*this)(1,0) * (*this)(0,2) * (*this)(2,3) + (*this)(0,0) * (*this)(1,2) * (*this)(2,3);

            mat(2,3) =  +(*this)(2,0) * (*this)(1,1) * (*this)(0,3) - (*this)(1,0) * (*this)(2,1) * (*this)(0,3) - (*this)(2,0) * (*this)(0,1) * (*this)(1,3)
                        +(*this)(0,0) * (*this)(2,1) * (*this)(1,3) + (*this)(1,0) * (*this)(0,1) * (*this)(2,3) - (*this)(0,0) * (*this)(1,1) * (*this)(2,3);

            mat(3,3) =  +(*this)(1,0) * (*this)(2,1) * (*this)(0,2) - (*this)(2,0) * (*this)(1,1) * (*this)(0,2) + (*this)(2,0) * (*this)(0,1) * (*this)(1,2)
                        -(*this)(0,0) * (*this)(2,1) * (*this)(1,2) - (*this)(1,0) * (*this)(0,1) * (*this)(2,2) + (*this)(0,0) * (*this)(1,1) * (*this)(2,2);

            return mat / det();
        }

        friend std::ostream &operator<<(std::ostream &os,const Matrix4d<Type> &mat){
            os<<"["<<mat[0] <<','<<mat[4] <<','<<mat[8] <<','<<mat[12] <<']'<<'\n';
            os<<"["<<mat[1] <<','<<mat[5] <<','<<mat[9] <<','<<mat[13] <<']'<<'\n';
            os<<"["<<mat[2] <<','<<mat[6] <<','<<mat[10]<<','<<mat[14]<<']'<<'\n';
            os<<"["<<mat[3]<<','<<mat[7]<<','<<mat[11]<<','<<mat[15]<<']'<<'\n';
            return os;
        }
    protected:
    private:
        std::array<Type,16> m_mat;
    };
}

#endif //_XMATH_MATRIX_H_