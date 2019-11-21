#ifndef _XMATH_MATRIX_H_
#define _XMATH_MATRIX_H_

#include <cctype>
#include <array>
#include <initializer_list>
#include <type_traits>
#include <cmath>
#include "Helper.h"

#ifndef XMATH_EPS
#define XMATH_EPS 1e-5
#endif

namespace xmath{
    static const size_t Dynamic = 0;
    enum class Direction{
        right,
        left,
        up,
        down
    };

    /**@name Matrix
     * @brief class Matrix
     * @tparam Type the type of value
     * @tparam Row the row of the Matrix
     * @tparam Col the Col of the Matrix
     */
    template <class Type,size_t Row,size_t Col>
    class Matrix{
    public:
        using value_type = Type;
        static constexpr size_t Count = Row * Col;

        static Matrix createIdentity(){
            Matrix res;
            for(size_t i = 0;i < Row;++i){
                res(i,i) = 1;
            }
            return res;
        }

        /** @name Default Constructor
         *  @brief construct a zero matrix
         */
        Matrix(){
            for(auto &itr : m_data){
                itr = 0;
            }
        }
        /**@name construct a value matrix
         * @brief set all element to value
         * @param value The value will fill the matrix
         */
        explicit Matrix(Type value){
            for(auto &itr : m_data){
                itr = value;
            }
        }
        /**@name Construct matrix from a pointer
         * @brief be careful SEGMENT FAULT
         */
        explicit Matrix(const Type *ptr){
            for(int i = 0;i < Count;++i){
                m_data[i] = ptr[i];
            }
        }
        /**@name Constructor
         * @brief Construct a matrix from a sequence
         * @tparam Iterator the type of Iterator
         * @param beg begin iterator
         * @param end end iterator
         */
        template <class Iterator>
        Matrix(Iterator beg,Iterator end){
            for(auto itr = m_data.begin();beg != end && itr != m_data.end();++itr,++beg){
                *itr = *beg;
            }
        }
        /**@name Constructor
         * @brief initialize from a initialize_list
         * @param list The initialize_list
         */
        Matrix(std::initializer_list<Type> list){
            for(auto itr1 = list.begin(),itr2 = m_data.begin();
                itr1 != list.end() && itr2 != m_data.end();
                ++itr1,++itr2){
                *itr2 = *itr1;
            }
        }
        /**@name Construct a matrix from the other one
         * @brief Can use to change a Matrix's size
         * @note Be careful the SEGMENT FAULT error
         * @tparam Type2 The type of the other matrix
         * @tparam Row2 The Row of the other matrix
         * @tparam Col2 The Col of the other matrix
         * @param mat The other matrix
         */
        template<class Type2,size_t Row2,size_t Col2>
        explicit Matrix(const Matrix<Type2,Row2,Col2> &mat){
            static_assert(Count == Row2 * Col2,"The count of the Matrix must be equal");
            for(auto i = 0; i < Count;++i){
                m_data[i] = static_cast<Type>(mat[i]);
            }
        }
        Matrix(const Matrix &mat) = default;
        Matrix(Matrix &&mat)noexcept = default;
        ~Matrix() = default;

        /**@name operator=
         * @brief rebuild a Matrix from a initialize_list
         * @param list The initialize_list
         * @return this matrix
         */
        Matrix &operator=(std::initializer_list<Type> list){
            for(auto itr1 = list.begin(),itr2 = m_data.begin();
                itr1 != list.end() && itr2 != m_data.end();
                ++itr1,++itr2){
                *itr2 = *itr1;
            }
            return *this;
        }
        /**@name operator=
          * @brief Can use to change a Matrix's size
          * @note Be careful the SEGMENT FAULT error
          * @tparam Type2 The type of the other matrix
          * @tparam Row2 The Row of the other matrix
          * @tparam Col2 The Col of the other matrix
          * @param mat The other matrix
          * @return this matrix
          */
        template <class Type2,size_t Row2,size_t Col2>
        Matrix &operator=(const Matrix<Type2,Row2,Col2> &mat){
            static_assert(Count == Row2 * Col2,"The count of the Matrix must be equal");
            for(auto i = 0; i < Count;++i){
                m_data[i] = static_cast<Type>(mat[i]);
            }
            return *this;
        }
        Matrix &operator=(const Matrix &mat) = default;
        Matrix &operator=(Matrix &&) noexcept = default;

        /**@name getRowCount
         * @brief get the Row Count
         * @return the Row
         */
        constexpr size_t getRowCount()const noexcept{
            return Row;
        }
        /**@name getColCount
          * @brief get the Col Count
          * @return the Col
          */
        constexpr size_t getColCount()const noexcept{
            return Col;
        }

        /**@name operator()(x,y)
         * @brief Get the (x,y) of the matrix
         * @param x the x coordinate
         * @param y the y coordinate
         * @return the reference of the element
         */
        Type &operator()(size_t x,size_t y)noexcept{
            return m_data[x * Col + y];
        }
        const Type &operator()(size_t x,size_t y)const noexcept {
            return m_data[x * Col + y];
        }

        /**@name operator[]
         * @brief Get the element in the index of the matrix
         * @param index The index of the element
         * @return the reference of the element
         */
        Type &operator[](size_t index) noexcept{
            return m_data[index];
        }
        const Type &operator[](size_t index) const noexcept {
            return m_data[index];
        }

        /**@name operator [const] Type *()noexcept
         * @return a pointer of the array
         */
        operator Type *()noexcept {
            return m_data.data();
        }
        operator const Type *()const noexcept {
            return m_data.data();
        }

        /**@name identity
         * @brief set matrix as a identity
         * @tparam Type2 IGNORE
         * @tparam Row2 IGNORE
         * @tparam Col2 IGNORE
         * @return the identity matrix
         */
        template <class Type2 = Type,size_t Row2 = Row,size_t Col2 = Col>
        auto identity()
            -> std::enable_if_t<Row2 == Col2,Matrix<Type2,Row2,Col2>>{
            Matrix<Type2,Row2,Col2> res;
            for(size_t i = 0;i < Row2;++i){
                res(i,i) = 1;
            }
            return res;
        }

        /**@name translate
         * @brief get a translation from the vector
         * @tparam Type2 IGNORE
         * @tparam Row2 IGNORE
         * @tparam Col2 IGNORE
         * @return the translation matrix
         */
        template <class Type2 = Type,size_t Row2 = Row,size_t Col2 = Col>
        auto translate()
        -> std::enable_if_t<get_vector_length_v<Row2,Col2> == 3,Matrix<Type,4,4>>{
            return Matrix<Type,4,4>{
                1,0,0,m_data[0],
                0,1,0,m_data[1],
                0,0,1,m_data[2],
                0,0,0,1
            };
        }

        /**@name scale
         * @brief get the scale matrix
         * @tparam Type2 IGNORE
         * @tparam Row2 IGNORE
         * @tparam Col2 IGNORE
         * @return the scale matrix
         */
        template <class Type2 = Type,size_t Row2 = Row,size_t Col2 = Col>
        auto scale()
        -> std::enable_if_t<get_vector_length_v<Row2,Col2> == 3,Matrix<Type,4,4>>{
            return Matrix<Type,4,4>{
                    m_data[0],0        ,0        ,0,
                    0        ,m_data[1],0        ,0,
                    0        ,0        ,m_data[2],0,
                    0        ,0        ,0        ,1
            };
        }

        /**@name rotate
         * @brief get a rotation matrix which can rotate a vector surround by this vector
         * @warning only for 3d vector
         * @tparam Type2 IGNORE
         * @tparam Row2 IGNORE
         * @tparam Col2 IGNORE
         * @param theta the angle
         * @return the rotation matrix
         */
        template <class Type2 = Type,size_t Row2 = Row,size_t Col2 = Col>
        auto rotate(Type theta)
        -> std::enable_if_t<get_vector_length_v<Row2,Col2> == 3,Matrix<Type,4,4>>{
            auto tmp = normalize();
            auto u = tmp[0];
            auto v = tmp[1];
            auto w = tmp[2];
            //todo:need more tests
            return Matrix<Type2,4,4>{
                u*u+(1-u*u)*cos(theta)         ,u*v*(1-cos(theta))-w*sin(theta),u*w*(1-cos(theta))+v*sin(theta),0,
                u*v*(1-cos(theta))+w*sin(theta),v*v+(1-v*v)*cos(theta)         ,v*w*(1-cos(theta))-u*sin(theta),0,
                u*w*(1-cos(theta))-v*sin(theta),v*w*(1-cos(theta))+u*sin(theta),         w*w+(1-w*w)*cos(theta),0,
                0                              ,0                              ,0                              ,1
            };
        }

        /**@name rotate
        * @brief get a rotation matrix from a quaternion
        * @warning only for Quaternion(4d-row-vector)
        * @tparam Type2 IGNORE
        * @tparam Row2 IGNORE
        * @tparam Col2 IGNORE
        * @return the rotation matrix
        */
        template <class Type2 = Type,size_t Row2 = Row,size_t Col2 = Col>
        auto rotate()
        -> std::enable_if_t<is_row_vector_v<Row2,Col2> && get_vector_length_v<Row2,Col2> == 4,Matrix<Type,4,4>>{
            auto tmp = normalize();
            auto x = tmp[0];
            auto y = tmp[1];
            auto z = tmp[2];
            auto w = tmp[3];
            //todo:need more tests
            return Matrix<Type2,4,4>{
                //todo
            };
        }



        /**@name operator+
         * @brief Add two matrices
         * @param mat The other matrix
         * @return The new matrix
         */
        Matrix operator+(const Matrix &mat)const noexcept{
            Matrix ans;
            for(auto i = 0;i < Count;++i){
                ans.m_data[i] = m_data[i] + mat.m_data[i];
            }
            return ans;
        }
        /**@name operator+
         * @brief add matrix and value
         * @param val the value
         * @return the answer matrix
         */
        Matrix operator+(const Type &val)const noexcept {
            Matrix ans;
            for(size_t i = 0;i < Count;++i){
                ans.m_data[i] = m_data[i] + val;
            }
        }

        /**@name operator-
         * @brief Minus two matrices
         * @param mat The other matrix
         * @return The answer matrix
         */
        Matrix operator-(const Matrix &mat)const noexcept{
            Matrix ans;
            for(auto i = 0;i < Count;++i){
                ans.m_data[i] = m_data[i] - mat.m_data[i];
            }
            return ans;
        }
        /**@name operator-
         * @brief Minus matrix and value
         * @param value the value
         * @return The answer matrix
         */
        Matrix operator-(const Type &value)const noexcept{
            Matrix ans;
            for(auto i = 0;i < Count;++i){
                ans.m_data[i] = m_data[i] - value;
            }
            return ans;
        }
        /**@name operator*
          * @brief Multiple two matrices
          * @param mat The other matrix
          * @return The answer matrix
          */
        Matrix operator*(const Matrix &mat)const noexcept{
            Matrix ans;
            for(auto i = 0;i < Count;++i){
                ans.m_data[i] = m_data[i] * mat.m_data[i];
            }
            return ans;
        }
        /**@name operator*
          * @brief Multiple matrix and value
          * @param value the value
          * @return The answer matrix
          */
        Matrix operator*(const Type &value)const noexcept{
            Matrix ans;
            for(auto i = 0;i < Count;++i){
                ans.m_data[i] = m_data[i] * value;
            }
            return ans;
        }
        /**@name operator/
          * @brief Divide two matrices
          * @param mat The other matrix
          * @return The answer matrix
          */
        Matrix operator/(const Matrix &mat)const noexcept{
            Matrix ans;
            for(auto i = 0;i < Count;++i){
                ans.m_data[i] = m_data[i] / mat.m_data[i];
            }
            return ans;
        }
        /**@name operator/
          * @brief Divide matrix and value
          * @param value the value
          * @return The answer matrix
          */
        Matrix operator/(const Type &value)const noexcept{
            Matrix ans;
            for(auto i = 0;i < Count;++i){
                ans.m_data[i] = m_data[i] / value;
            }
            return ans;
        }


        ///I'm lazy
        Matrix &operator+=(const Matrix &mat)noexcept{
            return (*this = *this + mat);
        }
        Matrix &operator-=(const Matrix &mat)noexcept {
            return (*this = *this - mat);
        }
        Matrix &operator*=(const Matrix &mat)noexcept{
            return (*this = *this * mat);
        }
        Matrix &operator/=(const Matrix &mat)noexcept{
            return (*this = *this / mat);
        }
        Matrix &operator+=(const Type &value)noexcept{
            return (*this = *this + value);
        }
        Matrix &operator-=(const Type &value)noexcept {
            return (*this = *this - value);
        }
        Matrix &operator*=(const Type &value)noexcept{
            return (*this = *this * value);
        }
        Matrix &operator/=(const Type &value)noexcept{
            return (*this = *this / value);
        }


        /**@name operator==
         * @brief check if two matrices are equal
         * @param mat the other matrix
         * @return true if equal
         */
        bool operator==(const Matrix &mat)const noexcept {
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
        bool operator!=(const Matrix &mat)const noexcept {
            return !(*this == mat);
        }


        /**@name product
         * @brief compute the product of two matrices
         * @warning Be careful the condition of Product
         * @tparam Col2 the other matrix's Col
         * @param mat The other mat
         * @return the answer matrix
         */
        template <size_t Col2>
        Matrix<Type,Row,Col2> product(const Matrix<Type,Col,Col2> &mat)const noexcept{
            Matrix<Type,Row,Col2> res;
            for(size_t i = 0;i < Row;++i){
                for(size_t j = 0;j < Col2;++j){
                    for(size_t k = 0;k < Col;++k){
                        res(i,j) += (*this)(i,k) * mat(k,j);
                    }
                }
            }
            return res;
        }
        ///operator% 's priority is same as operator*
        template <size_t Col2>
        Matrix<Type,Row,Col2> operator%(const Matrix<Type,Col,Col2> &mat)const noexcept{
            return product(mat);
        }

        /**@name extend
         * @brief combine two matrices
         * @tparam dir The direction
         * @tparam Type2 IGNORE
         * @tparam Row2 IGNORE
         * @tparam Col2 IGNORE
         * @param mat the other matrix
         * @return the result matrix
         */
        template <Direction dir = Direction::right,class Type2 = Type,size_t Row2,size_t Col2>
        auto extend(const Matrix<Type2,Row2,Col2> &mat)const noexcept
            -> std::enable_if_t<dir == Direction::right && Row == Row2,Matrix<Type2,Row,Col+Col2>>{
            Matrix<Type2,Row,Col+Col2> res;
            for(size_t i = 0;i < Row;++i){
                for(size_t j = 0;j < Col;++j){
                    res(i,j) = (*this)(i,j);
                }
            }
            for(size_t i = 0;i < Row2;++i){
                for(size_t j = 0;j < Col2;++j){
                    res(i,j + Col) = mat(i,j);
                }
            }
            return res;
        }
        template <Direction dir,class Type2 = Type,size_t Row2,size_t Col2>
        auto extend(const Matrix<Type2,Row2,Col2> &mat)const noexcept
        -> std::enable_if_t<dir == Direction::left && Row == Row2,Matrix<Type2,Row,Col+Col2>>{
            Matrix<Type2,Row,Col+Col2> res;
            for(size_t i = 0;i < Row2;++i){
                for(size_t j = 0;j < Col2;++j){
                    res(i,j) = mat(i,j);
                }
            }
            for(size_t i = 0;i < Row;++i){
                for(size_t j = 0;j < Col;++j){
                    res(i,j + Col2) = (*this)(i,j);
                }
            }
            return res;
        }
        template <Direction dir,class Type2 = Type,size_t Row2,size_t Col2>
        auto extend(const Matrix<Type2,Row2,Col2> &mat)const noexcept
        -> std::enable_if_t<dir == Direction::up && Col == Col2,Matrix<Type2,Row+Row2,Col>>{
            Matrix<Type2,Row+Row2,Col> res;
            for(size_t i = 0;i < Row2;++i){
                for(size_t j = 0;j < Col2;++j){
                    res(i,j) = mat(i,j);
                }
            }
            for(size_t i = 0;i < Row;++i){
                for(size_t j = 0;j < Col;++j){
                    res(i + Row2,j) = (*this)(i,j);
                }
            }
            return res;
        }
        template <Direction dir,class Type2 = Type,size_t Row2,size_t Col2>
        auto extend(const Matrix<Type2,Row2,Col2> &mat)const noexcept
        -> std::enable_if_t<dir == Direction::down && Col == Col2,Matrix<Type2,Row+Row2,Col>>{
            Matrix<Type2,Row+Row2,Col> res;
            for(size_t i = 0;i < Row;++i){
                for(size_t j = 0;j < Col;++j){
                    res(i,j) = (*this)(i,j);
                }
            }
            for(size_t i = 0;i < Row2;++i){
                for(size_t j = 0;j < Col2;++j){
                    res(i + Row,j) = mat(i,j);
                }
            }
            return res;
        }

        /**@name cofactor
         * @brief get an element's cofactor
         * @warning Row and Col must be greater than 1
         * @tparam Type2 IGNORE
         * @tparam Row2 IGNORE
         * @tparam Col2 IGNORE
         * @param x element's x coordinate
         * @param y element's y coordinate
         * @return the cofactor
         */
        template<class Type2 = Type,size_t Row2 = Row,size_t Col2 = Col>
        auto cofactor(size_t x,size_t y)const noexcept
            -> std::enable_if_t<(Row2 > 1 && Col2 > 1),Matrix<Type2,Row2-1,Col2-1>>{
            Matrix<Type2,Row2-1,Col2-1> res;
            size_t k = 0;
            for(size_t i = 0;i < Row;++i){
                for(size_t j = 0;j < Col;++j){
                    if(i == x || j == y)
                        continue;
                    res[k++] = (*this)(i,j);
                }
            }
            return res;
        }

        /**@name det
         * @brief compute the determinant
         * @warning only valid for square matrix
         * @return the determinant
         */
        template <class Type2 = Type,size_t Row2 = Row,size_t Col2 = Col>
        auto det()const noexcept
        -> std::enable_if_t<Row2 == 1 && Col2 == 1,Type2>{
            return m_data[0];
        }
        template <class Type2 = Type,size_t Row2 = Row,size_t Col2 = Col>
        auto det()const noexcept
        -> std::enable_if_t<Row2 == 2 && Col2 == 2,Type2>{
            return m_data[0] * m_data[3] - m_data[2] * m_data[1];
        }
        template <class Type2 = Type,size_t Row2 = Row,size_t Col2 = Col>
        auto det()const noexcept
        -> std::enable_if_t<Row2 == 3 && Col2 == 3,Type2>{
            return    (*this)(0,0) * (*this)(1,1) * (*this)(2,2)
                     +(*this)(0,1) * (*this)(1,2) * (*this)(2,0)
                     +(*this)(0,2) * (*this)(1,0) * (*this)(2,1)
                     -(*this)(0,0) * (*this)(1,2) * (*this)(2,1)
                     -(*this)(0,1) * (*this)(1,0) * (*this)(2,2)
                     -(*this)(0,2) * (*this)(1,1) * (*this)(2,0);
        }
        template <class Type2 = Type,size_t Row2 = Row,size_t Col2 = Col>
        auto det()const noexcept
        -> std::enable_if_t<(Row2 == Col2 && Row2 > 3 && Col2 > 3),Type2>{
            Type2 res = 0.0;
            for(size_t i = 0; i < Row2;++i){
                res += (*this)(0,i) * cofactor(0,i).det() * (i % 2 == 0 ? 1.0 : -1.0);
            }
            return res;
        }

        /**@name adjoint
         * @brief get the adjoint
         * @warning only valid for square matrix
         * @tparam Type2 IGNORE
         * @tparam Row2 IGNORE
         * @tparam Col2 IGNORE
         * @return the adjoint matrix
         */
        template <class Type2 = Type,size_t Row2 = Row,size_t Col2 = Col>
        auto adjoint()const noexcept
            -> std::enable_if_t<Row2 == Col2,Matrix<Type2,Row2,Col2>>{
            Matrix<Type2,Row2,Col2> res;
            for(int i = 0;i < Row2;++i){
                for(int j = 0;j < Col2;++j){
                    res(i,j) = (i + j) % 2 == 1 ? -cofactor(i,j).det() : cofactor(i,j).det();
                }
            }
            return res.transpose();
        }

        /**@name inverse
         * @brief get the inverse matrix
         * @tparam Type2 IGNORE
         * @tparam Row2 IGNORE
         * @tparam Col2 IGNORE
         * @return the inverse matrix
         */
        template <class Type2 = Type,size_t Row2 = Row,size_t Col2 = Col>
        auto inverse()const noexcept
        -> std::enable_if_t<Row2 == Col2,Matrix<Type2,Row2,Col2>>{
            return adjoint() / det();
        }

        /**@name dot
         * @brief compute the dot product between two VECTOR
         * @tparam Row2 The Row of vector
         * @tparam Col2 The Col of vector
         * @param vec the vector
         * @return a scalar which equals to the dot product
         */
        template <size_t Row2,size_t Col2>
        auto dot(const Matrix<Type,Row2,Col2> &vec) const noexcept
            -> std::enable_if_t<
                    is_vector_v<Row,Col> && is_vector_v<Row2,Col2>,
                    Type>{
            static_assert(get_vector_length_v<Row,Col> == get_vector_length_v<Row2,Col2>,"The length of vector must be equal");
            Type ans = 0;
            for(size_t i = 0;i < Count; ++i){
                ans += m_data[i] * vec[i];
            }
            return ans;
        }


        /**@name cross
         * @brief compute two 3d vectors' cross product
         * @warning These two vectors must be 3-dimension
         * @tparam Row2 the row of the vector
         * @tparam Col2 the col of the vector
         * @param vec the vector
         * @return the cross product vector
         */
        template <size_t Row2,size_t Col2>
        auto cross(const Matrix<Type,Row2,Col2> &vec)const noexcept
            -> std::enable_if_t<
                get_vector_length_v<Row,Col> == 3 && get_vector_length_v<Row2,Col2> == 3,
                Matrix<Type,1,3>> {
            return Matrix<Type,1,3>{
                m_data[1] * vec[2] - vec[1] * m_data[2],
                m_data[2] * vec[0] - vec[2] * m_data[0],
                m_data[0] * vec[1] - vec[0] * m_data[1]
            };
        }

        /**@name cross
         * @brief compute two quaternion' cross product
         * @tparam Row2 IGNORE
         * @tparam Col2 IGNORE
         * @param qut the quaternion
         * @return the cross product quaternion
         */
        template <size_t Row2,size_t Col2>
        auto cross(const Matrix<Type,Row2,Col2> &qut)const noexcept
        -> std::enable_if_t<
                get_vector_length_v<Row,Col> == 4 && get_vector_length_v<Row2,Col2> == 4,
                Matrix<Type,1,4>> {
            return Matrix<Type,1,4>{
                m_data[3] * qut[0] + m_data[0] * qut[3] + m_data[2] * qut[1] - m_data[1] * qut[2],
                m_data[3] * qut[1] + m_data[1] * qut[3] + m_data[0] * qut[2] - m_data[2] * qut[0],
                m_data[3] * qut[2] + m_data[2] * qut[3] + m_data[1] * qut[0] - m_data[0] * qut[1],
                m_data[3] * qut[3] - m_data[0] * qut[0] - m_data[1] * qut[1] - m_data[2] * qut[2]
            };
        }

        /**@name length
         * @brief get the length of this vector
         * @tparam Type2 IGONRE
         * @tparam Row2 IGNORE
         * @tparam Col2 IGNORE
         * @return the length
         */
        template <class Type2 = Type,size_t Row2 = Row,size_t Col2 = Col>
        auto length()const noexcept
            -> std::enable_if_t<is_vector_v<Row2,Col2>,Type2>{
            Type2 len = 0;
            for(const auto &itr : m_data){
                len += itr * itr;
            }
            return std::sqrt(len);
        }

        /**@name length2
         * @brief get the square of length of this vector(avoid sqrt)
         * @tparam Type2 IGNORE
         * @tparam Row2 IGNORE
         * @tparam Col2 IGNORE
         * @return the length's square
         */
        template <class Type2 = Type,size_t Row2 = Row,size_t Col2 = Col>
        auto length2()const noexcept
        -> std::enable_if_t<is_vector_v<Row2,Col2>,Type2>{
            Type2 len = 0;
            for(const auto &itr : m_data){
                len += itr * itr;
            }
            return len;
        }

        template <class Type2 = Type,size_t Row2 = Row,size_t Col2 = Col>
        auto normalize()const noexcept
        -> std::enable_if_t<is_vector_v<Row2,Col2>,Matrix<Type2,Row2,Col2>>{
            return (*this) / length();
        }

        /**@name transpose
         * @brief transpose a matrix
         * @details [1,2] =><br>[1]<br>[2]
         * @return the transposed matrix
         */
        Matrix<Type,Col,Row> transpose()const noexcept{
            Matrix<Type,Col,Row> res;
            for(size_t i = 0; i < Row;++i){
                for(size_t j = 0; j < Col;++j){
                    res(j,i) = (*this)(i,j);
                }
            }
            return res;
        }
        Matrix<Type,Col,Row> operator~()const noexcept{
           return transpose();
        }

        /**@name sub
         * @brief Get the sub matrix in the position
         * @note Be careful the SEGMENT FAULT
         * @tparam Row2 The row of the sub matrix
         * @tparam Col2 The Col of the sub matrix
         * @param x The x coordinate of the sub matrix
         * @param y The y coordinate of the sub matrix
         * @return the sub matrix
         */
        template <size_t Row2,size_t Col2>
        Matrix<Type,Row2,Col2> sub(size_t x,size_t y)const noexcept{
            Matrix<Type,Row2,Col2> res;
            for(size_t i = 0;i < Row2;++i){
                for(size_t j = 0;j < Col2; ++j){
                    res(i,j) = (*this)(x+i,y+j);
                }
            }
            return res;
        }

        /**@name row
         * @brief get a row of this matrix
         * @param r the row
         * @return a row vector
         */
        Matrix<Type,1,Col> row(size_t r)const noexcept{
            return sub<1,Col>(r,0);
        }
        /**@name col
         * @brief get a col of this matrix
         * @param c the col
         * @return a col vector
         */
        Matrix<Type,Row,1> col(size_t c)const noexcept{
            return sub<Row,1>(0,c);
        }

        /**@name operator<<
         * @brief Print the matrix to ostream
         * @param os The ostream object
         * @param mat The Matrix
         * @return return the reference of os
         */
        friend std::ostream &operator<<(std::ostream &os,const Matrix &mat){
            auto i = 0;
            for(const auto &itr : mat.m_data){
                if(i == 0){
                    os << '[';
                }
                os << itr;
                if(i == Col - 1){
                    i = 0;
                    os << "]\n";
                }else{
                    ++i;
                    os << ',';
                }
            }
            return os;
        }
    protected:
    private:
        std::array<value_type,Count> m_data;
    };

    template <class Type>
    class Matrix<Type,Dynamic,Dynamic>{
        //todo
    };

    template <class Type>
    using Scalar = Matrix<Type,1,1>;
    template <class Type,size_t Size>
    using RowVector = Matrix<Type,1,Size>;
    template <class Type,size_t Size>
    using ColVector = Matrix<Type,Size,1>;
    template <class Type,size_t Size>
    using Vector = ColVector<Type,Size>;
    template <class Type,size_t Size>
    using SquareMatrix = Matrix<Type,Size,Size>;

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

    ///xyzw
    using Quaternionf = RowVector<float,4>;
    using Quaterniond = RowVector<double,4>;
    using Quaternioni = RowVector<int,4>;
    using Quaternionui = RowVector<unsigned int,4>;

    using Matrix2x2f = Matrix<float,2,2>;
    using Matrix2x3f = Matrix<float,2,3>;
    using Matrix2x4f = Matrix<float,2,4>;
    using Matrix3x2f = Matrix<float,3,2>;
    using Matrix3x3f = Matrix<float,3,3>;
    using Matrix3x4f = Matrix<float,3,4>;
    using Matrix4x2f = Matrix<float,4,2>;
    using Matrix4x3f = Matrix<float,4,3>;
    using Matrix4x4f = Matrix<float,4,4>;

    using Matrix2x2d = Matrix<double,2,2>;
    using Matrix2x3d = Matrix<double,2,3>;
    using Matrix2x4d = Matrix<double,2,4>;
    using Matrix3x2d = Matrix<double,3,2>;
    using Matrix3x3d = Matrix<double,3,3>;
    using Matrix3x4d = Matrix<double,3,4>;
    using Matrix4x2d = Matrix<double,4,2>;
    using Matrix4x3d = Matrix<double,4,3>;
    using Matrix4x4d = Matrix<double,4,4>;

    using Matrix2x2i = Matrix<int,2,2>;
    using Matrix2x3i = Matrix<int,2,3>;
    using Matrix2x4i = Matrix<int,2,4>;
    using Matrix3x2i = Matrix<int,3,2>;
    using Matrix3x3i = Matrix<int,3,3>;
    using Matrix3x4i = Matrix<int,3,4>;
    using Matrix4x2i = Matrix<int,4,2>;
    using Matrix4x3i = Matrix<int,4,3>;
    using Matrix4x4i = Matrix<int,4,4>;

    using Matrix2x2ui = Matrix<unsigned int,2,2>;
    using Matrix2x3ui = Matrix<unsigned int,2,3>;
    using Matrix2x4ui = Matrix<unsigned int,2,4>;
    using Matrix3x2ui = Matrix<unsigned int,3,2>;
    using Matrix3x3ui = Matrix<unsigned int,3,3>;
    using Matrix3x4ui = Matrix<unsigned int,3,4>;
    using Matrix4x2ui = Matrix<unsigned int,4,2>;
    using Matrix4x3ui = Matrix<unsigned int,4,3>;
    using Matrix4x4ui = Matrix<unsigned int,4,4>;

    using Matrix2f = Matrix2x2f;
    using Matrix3f = Matrix3x3f;
    using Matrix4f = Matrix4x4f;

    using Matrix2d = Matrix2x2d;
    using Matrix3d = Matrix3x3d;
    using Matrix4d = Matrix4x4d;

    using Matrix2i = Matrix2x2i;
    using Matrix3i = Matrix3x3i;
    using Matrix4i = Matrix4x4i;

    using Matrix2ui = Matrix2x2ui;
    using Matrix3ui = Matrix3x3ui;
    using Matrix4ui = Matrix4x4ui;
}

#endif //_XMATH_MATRIX_H_