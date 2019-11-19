#ifndef _XMATH_MATRIX_H_
#define _XMATH_MATRIX_H_

#include <cctype>
#include <array>
#include <initializer_list>
#include <type_traits>
#include "Helper.h"

#include <XTest/XTest.h>

namespace xmath{
    static const size_t Dynamic = 0;

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
            for(int i = 0;i < Row;++i){
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

        /**@name opeartor()(x,y)
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
        /**@name operator/
          * @brief Multiple two matrices
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


        template <size_t Col2>
        Matrix<Type,Row,Col2> product(const Matrix<Type,Col,Col2> &mat)const noexcept{
            Matrix<Type,Row,Col2> res;

            return res;
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

        /**@name transpose
         * @brief transpose a matrix
         * @details [1,2] =><br>[1]<br>[2]
         * @return the transposed matrix
         */
        Matrix<Type,Col,Row> transpose()const noexcept{
            Matrix<Type,Col,Row> res;
            for(size_t i = 0; i < Row;++i){
                for(size_t j = 0; j < Col;++j){
                    res(j,i) = this->operator()(i,j);
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
}

#endif //_XMATH_MATRIX_H_