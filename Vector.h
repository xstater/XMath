#ifndef _XMATH_VECTOR_H_
#define _XMATH_VECTOR_H_

#include <cmath>
#include "Matrix.h"

namespace xmath{
    template <class Type,size_t Count>
    class Vector{
    public:
        using iterator = typename std::array<Type,Count>::iterator;
        using const_iterator = typename std::array<Type,Count>::const_iterator;
        using reverse_iterator = typename std::array<Type,Count>::reverse_iterator;
        using const_reverse_iterator = typename std::array<Type,Count>::const_reverse_iterator;

        constexpr size_t count()const noexcept{
            return Count;
        }

        Vector(){
            for(auto &itr : m_data){
                itr = 0;
            }
        }
        explicit Vector(Type val){
            for(auto &itr : m_data){
                itr = val;
            }
        }
        explicit Vector(const Type *ptr){
            for(size_t i = 0;i < Count;++i){
                m_data[i] = ptr[i];
            }
        }
        template <class Iterator>
        explicit Vector(Iterator beg,Iterator end){
            for(auto itr1 = beg,itr2 = m_data.begin();
                itr1 != end && itr2 != m_data.end();
                ++itr1,++itr2){
                *itr2 = *itr1;
            }
        }
        explicit Vector(std::initializer_list<Type> list){
            for(auto itr1 = list.begin(),itr2 = m_data.begin();
                itr1 != list.end() && itr2 != m_data.end();
                ++itr1,++itr2){
                *itr2 = *itr1;
            }
        }
        explicit Vector(const Matrix<Type,1,Count> &matrix){
            for(auto itr1 = matrix.begin(),itr2 = m_data.begin();
                itr1 != matrix.end() && itr2 != m_data.end();
                ++itr1,++itr2){
                *itr2 = *itr1;
            }
        }
        explicit Vector(const Matrix<Type,Count,1> &matrix){
            for(auto itr1 = matrix.begin(),itr2 = m_data.begin();
                itr1 != matrix.end() && itr2 != m_data.end();
                ++itr1,++itr2){
                *itr2 = *itr1;
            }
        }
        Vector(const Vector &vec) = default;
        Vector(Vector &&) = default;
        ~Vector() = default;

        Vector &operator=(const Matrix<Type,1,Count> &matrix){
            for(size_t i = 0;i < Count;++i){
                m_data[i] = matrix[i];
            }
            return *this;
        }
        Vector &operator=(const Matrix<Type,Count,1> &matrix){
            for(size_t i = 0;i < Count;++i){
                m_data[i] = matrix[i];
            }
            return *this;
        }
        Vector &operator=(const Vector &mat) = default;
        Vector &operator=(Vector &&) noexcept = default;

        Type &operator[](size_t index) noexcept{
            return m_data[index];
        }
        const Type &operator[](size_t index) const noexcept {
            return m_data[index];
        }

        operator Type *()noexcept {
            return m_data.data();
        }
        operator const Type *()const noexcept {
            return m_data.data();
        }

        Type *data()noexcept {
            return m_data.data();
        }
        const Type *data()const noexcept {
            return m_data.data();
        }

        Matrix<Type,1,Count> toRow()const noexcept{
            return Matrix<Type,1,Count>(m_data.data());
        }
        Matrix<Type,Count,1> toCol()const noexcept{
            return Matrix<Type,Count,1>(m_data.data());
        }

        Vector operator+(const Vector &mat)const noexcept{
            Vector ans;
            for(auto i = 0;i < Count;++i){
                ans.m_data[i] = m_data[i] + mat.m_data[i];
            }
            return ans;
        }

        Vector operator+(const Type &val)const noexcept {
            Vector ans;
            for(size_t i = 0;i < Count;++i){
                ans.m_data[i] = m_data[i] + val;
            }
        }

        Vector operator-(const Vector &mat)const noexcept{
            Vector ans;
            for(auto i = 0;i < Count;++i){
                ans.m_data[i] = m_data[i] - mat.m_data[i];
            }
            return ans;
        }

        Vector operator-(const Type &value)const noexcept{
            Vector ans;
            for(auto i = 0;i < Count;++i){
                ans.m_data[i] = m_data[i] - value;
            }
            return ans;
        }
        Vector operator-()const noexcept{
            Vector ans;
            for(auto i = 0;i < Count;++i){
                ans.m_data[i] = -m_data[i];
            }
            return ans;
        }

        Vector operator*(const Vector &mat)const noexcept{
            Vector ans;
            for(auto i = 0;i < Count;++i){
                ans.m_data[i] = m_data[i] * mat.m_data[i];
            }
            return ans;
        }

        Vector operator*(const Type &value)const noexcept{
            Vector ans;
            for(auto i = 0;i < Count;++i){
                ans.m_data[i] = m_data[i] * value;
            }
            return ans;
        }

        Vector operator/(const Vector &mat)const noexcept{
            Vector ans;
            for(auto i = 0;i < Count;++i){
                ans.m_data[i] = m_data[i] / mat.m_data[i];
            }
            return ans;
        }

        Vector operator/(const Type &value)const noexcept{
            Vector ans;
            for(auto i = 0;i < Count;++i){
                ans.m_data[i] = m_data[i] / value;
            }
            return ans;
        }

        Vector &operator+=(const Vector &mat)noexcept{
            for(size_t i = 0;i < Count;++i){
                m_data += mat.m_data[i];
            }
            return *this;
        }
        Vector &operator-=(const Vector &mat)noexcept {
            for(size_t i = 0;i < Count;++i){
                m_data -= mat.m_data[i];
            }
            return *this;
        }
        Vector &operator*=(const Vector &mat)noexcept{
            for(size_t i = 0;i < Count;++i){
                m_data *= mat.m_data[i];
            }
            return *this;
        }
        Vector &operator/=(const Vector &mat)noexcept{
            for(size_t i = 0;i < Count;++i){
                m_data /= mat.m_data[i];
            }
            return *this;
        }
        Vector &operator+=(const Type &value)noexcept{
            for(size_t i = 0;i < Count;++i){
                m_data += value;
            }
            return *this;
        }
        Vector &operator-=(const Type &value)noexcept {
            for(size_t i = 0;i < Count;++i){
                m_data -= value;
            }
            return *this;
        }
        Vector &operator*=(const Type &value)noexcept{
            for(size_t i = 0;i < Count;++i){
                m_data *= value;
            }
            return *this;
        }
        Vector &operator/=(const Type &value)noexcept{
            for(size_t i = 0;i < Count;++i){
                m_data /= value;
            }
            return *this;
        }


        bool operator==(const Vector &mat)const noexcept {
            for(auto itr1 = m_data.begin(),
                        itr2 = mat.m_data.begin();
                itr1 != m_data.end();
                ++itr1,++itr2){
                if(std::abs(*itr1 - *itr2) > XMATH_EPS){
                    return false;
                }
            }
            return true;
        }
        bool operator!=(const Vector &mat)const noexcept {
            return !(*this == mat);
        }


        Type dot(const Vector &vec) const noexcept{
            Type ans = 0;
            for(size_t i = 0;i < Count; ++i){
                ans += m_data[i] * vec.m_data[i];
            }
            return ans;
        }

        template <size_t Count2>
        auto cross(const Vector<Type,Count2> &vec)const noexcept
        -> std::enable_if_t<Count == 3 && Count2 == 3,Vector<Type,3>> {
            return Vector<Type,3>{
                    m_data[1] * vec[2] - vec[1] * m_data[2],
                    m_data[2] * vec[0] - vec[2] * m_data[0],
                    m_data[0] * vec[1] - vec[0] * m_data[1]
            };
        }


        Type length()const noexcept{
            Type len = 0;
            for(auto itr = m_data.cbegin();itr != m_data.cend();++itr){
                len += *itr * *itr;
            }
            return std::sqrt(len);
        }

        Type length2()const noexcept{
            Type len = 0;
            for(auto itr = m_data.cbegin();itr != m_data.cend();++itr){
                len += *itr * *itr;
            }
            return len;
        }

        Vector normalize()const noexcept{
            return Vector(this->operator/(length()));
        }

        template <class Type2 = Type,size_t Count2 = Count>
        auto translate()
        -> std::enable_if_t<Count == 3 && Count2 == 3,Matrix<Type,4,4>>{
            return Matrix<Type,4,4>{
                    1,0,0,m_data[0],//x
                    0,1,0,m_data[1],//y
                    0,0,1,m_data[2],//z
                    0,0,0,1
            };
        }
        template <class Type2 = Type,size_t Count2 = Count>
        auto translate()
        -> std::enable_if_t<Count == 4 && Count2 == 4,Matrix<Type,4,4>>{
            return Matrix<Type,4,4>{
                    1,0,0,m_data[0],//x
                    0,1,0,m_data[1],//y
                    0,0,1,m_data[2],//z
                    0,0,0,m_data[3] //w
            };
        }

        template <class Type2 = Type,size_t Count2 = Count>
        auto scale()
        -> std::enable_if_t<Count == 3 && Count2 == 3,Matrix<Type,4,4>>{
            return Matrix<Type,4,4>{
                    m_data[0],0        ,0        ,0,
                    0        ,m_data[1],0        ,0,
                    0        ,0        ,m_data[2],0,
                    0        ,0        ,0        ,1
            };
        }

        template <class Type2 = Type,size_t Count2 = Count>
        auto rotate(Type angle)
        -> std::enable_if_t<Count == 3 && Count2 == 3,Matrix<Type,4,4>>{
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
            }.transpose();
        }

        template <class Type2 = Type,size_t Count2 = Count>
        auto rotate()
        -> std::enable_if_t<Count == 3 && Count2 == 3,Matrix<Type,4,4>>{
//            auto ac = cos(m_data[0]);
//            auto as = sin(m_data[0]);
//            auto bc = cos(m_data[1]);
//            auto bs = sin(m_data[1]);
//            auto cc = cos(m_data[2]);
//            auto cs = sin(m_data[2]);
//
//            Matrix4d ma{
//                1,  0, 0,0,
//                0, ac,as,0,
//                0,-as,ac,0,
//                0,  0, 0,1
//            };
            return Vector<Type,3>{1,0,0}.rotate(m_data[0])
                 % Vector<Type,3>{0,1,0}.rotate(m_data[1])
                 % Vector<Type,3>{0,0,1}.rotate(m_data[2]);
        }

        template <class Type2 = Type,size_t Count2 = Count>
        auto lookAt(const Vector<Type2,Count2> &target,const Vector<Type2,Count2> &upDir)
        -> std::enable_if_t<Count == 3 && Count2 == 3,Matrix<Type,4,4>>{
            auto forward = (target - *this).normalize();
            auto up = upDir;

            auto side = forward.cross(up).normalize();
            up = side.cross(forward);

            auto m = Matrix<Type,4,4>{
                    side[0],    side[1],    side[2],0,
                      up[0],      up[1],      up[2],0,
                -forward[0],-forward[1],-forward[2],0,
                          0,          0,          0,1
            };
            return m % this->operator-().translate();
        }

        /**@name frustum
         * @note top,bottom,left,right,near,far
         * @note   0,     1,   2,    3,   4,  5
         * @tparam Type2
         * @tparam Count2
         * @return the frustum matrix
         */
        template <class Type2 = Type,size_t Count2 = Count>
        auto frustum()
        -> std::enable_if_t<Count == 6 && Count2 == 6,Matrix<Type,4,4>>{
            Type2 inv_width = 1.0 / (m_data[3] - m_data[2]);
            Type2 inv_height = 1.0 / (m_data[0] - m_data[1]);
            Type2 inv_depth = 1.0 / (m_data[5] - m_data[4]);

            Type2 double_near = 2.0 * m_data[4];

            return Matrix<Type,4,4>{
                double_near * inv_width,                       0, (m_data[2] + m_data[3]) * inv_width ,                                    0,
                                      0,double_near * inv_height, (m_data[0] + m_data[1]) * inv_height,                                    0,
                                      0,                       0,-(m_data[5] + m_data[4]) * inv_depth ,- double_near * m_data[5] * inv_depth,
                                      0,                       0,                                 -1.0,                                    0
            };
        }

        /**@name ortho
         * @note top,bottom,left,right,near,far
         * @note   0,     1,   2,    3,   4,  5
         * @tparam Type2
         * @tparam Count2
         * @return the frustum matrix
         */
        template <class Type2 = Type,size_t Count2 = Count>
        auto ortho()
        -> std::enable_if_t<Count == 6 && Count2 == 6,Matrix<Type,4,4>>{
            Type2 inv_width = 1.0 / (m_data[3] - m_data[2]);
            Type2 inv_height = 1.0 / (m_data[0] - m_data[1]);
            Type2 inv_depth = 1.0 / (m_data[5] - m_data[4]);

            return Matrix<Type,4,4>{
                    2 * inv_width,             0,             0,-(m_data[3] + m_data[2]) * inv_width ,
                                0,2 * inv_height,             0,-(m_data[0] + m_data[1]) * inv_height,
                                0,             0,-2 * inv_depth,-(m_data[4] + m_data[5]) * inv_depth ,
                                0,             0,             0,                                    1
            };
        }


        /**@name frustum
         * @note aspect,fov,near,far
         * @note      0,  1,   2,  3
         * @tparam Type2
         * @tparam Count2
         * @return the frustum matrix
         */
        template <class Type2 = Type,size_t Count2 = Count>
        auto frustum()
        -> std::enable_if_t<Count == 4 && Count2 == 4,Matrix<Type,4,4>>{
            Type2 cot_fov2 = 1.0 / std::tan(m_data[1] / 2.0);
            Type2 depth = m_data[2] - m_data[3];//near - far
            //todo:need more tests
            return Matrix < Type,4,4 > {
                cot_fov2 / m_data[0],       0,                              0,                                0,
                                   0,cot_fov2,                              0,                                0,
                                   0,       0,(m_data[2] + m_data[3]) / depth,2 * m_data[2] * m_data[3] / depth,
                                   0,       0,                             -1,                                0
            };
        }

            iterator begin()noexcept{
            return m_data.begin();
        }
        iterator end()noexcept {
            return m_data.end();
        }
        const_iterator cbegin()const noexcept{
            return m_data.cbegin();
        }
        const_iterator cend()const noexcept{
            return m_data.cend();
        }
        reverse_iterator rbegin()noexcept{
            return m_data.rbegin();
        }
        reverse_iterator rend()noexcept{
            return m_data.rend();
        }
        const_reverse_iterator crbegin()const noexcept{
            return m_data,crbegin();
        }
        const_reverse_iterator crend()const noexcept{
            return m_data.crend();
        }

        friend Vector operator%(const Matrix<Type,Count,Count> &mat,const Vector &vec){
            Vector ans;
            for(size_t i = 0;i < Count;++i){
                for(size_t j = 0;j < Count;++j){
                    ans[i] += mat(i,j) * vec[j];
                }
            }
            return ans;
        }

        friend std::ostream &operator<<(std::ostream &os,const Vector &vector){
            os << '[';
            for(size_t i = 0; i < vector.count() - 1;++i){
                os << vector[i] << ',';
            }
            os << vector[vector.count() - 1] << ']';
            return os;
        }

    private:
        std::array<Type,Count> m_data;
    };

    template <size_t Count>
    using Vectorf = Vector<float,Count>;
    template <size_t Count>
    using Vectord = Vector<double,Count>;
    template <size_t Count>
    using Vectori = Vector<int,Count>;
    template <size_t Count>
    using Vectorui = Vector<unsigned int,Count>;

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
