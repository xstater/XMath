#ifndef _XMATH_MATRIX_H_
#define _XMATH_MATRIX_H_

#include <cctype>
#include <array>
#include <initializer_list>

namespace xmath{
    static const size_t Dynamic = 0;

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
        /**@name Construct matrix from a pointer
         * @brief be careful SEGMENT FAULT
         */
        Matrix(const Type *ptr){
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
        Matrix(const Matrix<Type2,Row2,Col2> &mat){
            static_assert(Count == Row2 * Col2,"The count of the Matrix must be equal");
            for(auto i = 0; i < Count;++i){
                m_data[i] = static_cast<Type>(mat[i]);
            }
        }
        Matrix(const Matrix &mat) = default;
        Matrix(Matrix &&mat) = default;
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
        Matrix &operator=(Matrix &&) = default;

        /**@name opeartor()(x,y)
         * @brief Get the (x,y) of the matrix
         * @param x the x coordinate
         * @param y the y coordinate
         * @return the reference of the element
         */
        Type &operator()(size_t x,size_t y)noexcept{
            return m_data[x * Row + y];
        }
        const Type &operator()(size_t x,size_t y)const noexcept {
            return m_data[x * Row + y];
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