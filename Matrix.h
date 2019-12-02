#ifndef _XMATH_MATRIX_H_
#define _XMATH_MATRIX_H_

#include <iostream>

#if !defined(XMATH_EPS)
#define XMATH_EPS 1e-5
#endif

namespace xmath{
    enum class Direction{
        right,
        left,
        up,
        down
    };

    template <class Type,size_t Row,size_t Col>
    class Matrix{
    public:
        using value_type = Type;
        static constexpr size_t Count = Row * Col;
        using iterator = typename std::array<Type,Count>::iterator;
        using const_iterator = typename std::array<Type,Count>::const_iterator;
        using reverse_iterator = typename std::array<Type,Count>::reverse_iterator;
        using const_reverse_iterator = typename std::array<Type,Count>::const_reverse_iterator;

        constexpr size_t count()const noexcept{
            return Count;
        }

        Matrix(){
            for(auto &itr : m_data){
                itr = 0;
            }
        }
        explicit Matrix(Type value){
            for(auto &itr : m_data){
                itr = value;
            }
        }
        explicit Matrix(const Type *ptr){
            for(int i = 0;i < Count;++i){
                m_data[i] = ptr[i];
            }
        }
        template <class Iterator>
        Matrix(Iterator beg,Iterator end){
            for(auto itr = m_data.begin();beg != end && itr != m_data.end();++itr,++beg){
                *itr = *beg;
            }
        }
        Matrix(std::initializer_list<Type> list){
            for(auto itr1 = list.begin(),itr2 = m_data.begin();
                itr1 != list.end() && itr2 != m_data.end();
                ++itr1,++itr2){
                *itr2 = *itr1;
            }
        }
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

        Matrix &operator=(std::initializer_list<Type> list){
            for(auto itr1 = list.begin(),itr2 = m_data.begin();
                itr1 != list.end() && itr2 != m_data.end();
                ++itr1,++itr2){
                *itr2 = *itr1;
            }
            return *this;
        }

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

        constexpr size_t getRowCount()const noexcept{
            return Row;
        }
        constexpr size_t getColCount()const noexcept{
            return Col;
        }

        Type &operator()(size_t x,size_t y)noexcept{
            return m_data[x * Col + y];
        }
        const Type &operator()(size_t x,size_t y)const noexcept {
            return m_data[x * Col + y];
        }

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

        template <class Type2 = Type,size_t Row2 = Row,size_t Col2 = Col>
        auto identity()
        -> std::enable_if_t<Row2 == Col2,Matrix<Type2,Row2,Col2>>{
            Matrix<Type2,Row2,Col2> res;
            for(size_t i = 0;i < Row2;++i){
                res(i,i) = 1;
            }
            return res;
        }

        Matrix operator+(const Matrix &mat)const noexcept{
            Matrix ans;
            for(auto i = 0;i < Count;++i){
                ans.m_data[i] = m_data[i] + mat.m_data[i];
            }
            return ans;
        }

        Matrix operator+(const Type &val)const noexcept {
            Matrix ans;
            for(size_t i = 0;i < Count;++i){
                ans.m_data[i] = m_data[i] + val;
            }
        }

        Matrix operator-(const Matrix &mat)const noexcept{
            Matrix ans;
            for(auto i = 0;i < Count;++i){
                ans.m_data[i] = m_data[i] - mat.m_data[i];
            }
            return ans;
        }

        Matrix operator-(const Type &value)const noexcept{
            Matrix ans;
            for(auto i = 0;i < Count;++i){
                ans.m_data[i] = m_data[i] - value;
            }
            return ans;
        }
        Matrix operator-()const noexcept{
            Matrix ans;
            for(auto i = 0;i < Count;++i){
                ans.m_data[i] = -m_data[i];
            }
            return ans;
        }

        Matrix operator*(const Matrix &mat)const noexcept{
            Matrix ans;
            for(auto i = 0;i < Count;++i){
                ans.m_data[i] = m_data[i] * mat.m_data[i];
            }
            return ans;
        }

        Matrix operator*(const Type &value)const noexcept{
            Matrix ans;
            for(auto i = 0;i < Count;++i){
                ans.m_data[i] = m_data[i] * value;
            }
            return ans;
        }

        Matrix operator/(const Matrix &mat)const noexcept{
            Matrix ans;
            for(auto i = 0;i < Count;++i){
                ans.m_data[i] = m_data[i] / mat.m_data[i];
            }
            return ans;
        }

        Matrix operator/(const Type &value)const noexcept{
            Matrix ans;
            for(auto i = 0;i < Count;++i){
                ans.m_data[i] = m_data[i] / value;
            }
            return ans;
        }

        Matrix &operator+=(const Matrix &mat)noexcept{
            for(size_t i = 0;i < Count;++i){
                m_data += mat.m_data[i];
            }
            return *this;
        }
        Matrix &operator-=(const Matrix &mat)noexcept {
            for(size_t i = 0;i < Count;++i){
                m_data -= mat.m_data[i];
            }
            return *this;
        }
        Matrix &operator*=(const Matrix &mat)noexcept{
            for(size_t i = 0;i < Count;++i){
                m_data *= mat.m_data[i];
            }
            return *this;
        }
        Matrix &operator/=(const Matrix &mat)noexcept{
            for(size_t i = 0;i < Count;++i){
                m_data /= mat.m_data[i];
            }
            return *this;
        }
        Matrix &operator+=(const Type &value)noexcept{
            for(size_t i = 0;i < Count;++i){
                m_data += value;
            }
            return *this;
        }
        Matrix &operator-=(const Type &value)noexcept {
            for(size_t i = 0;i < Count;++i){
                m_data -= value;
            }
            return *this;
        }
        Matrix &operator*=(const Type &value)noexcept{
            for(size_t i = 0;i < Count;++i){
                m_data *= value;
            }
            return *this;
        }
        Matrix &operator/=(const Type &value)noexcept{
            for(size_t i = 0;i < Count;++i){
                m_data /= value;
            }
            return *this;
        }


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

        template <size_t Col2>
        Matrix<Type,Row,Col2> operator%(const Matrix<Type,Col,Col2> &mat)const noexcept{
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

        template <class Type2 = Type,size_t Row2 = Row,size_t Col2 = Col>
        auto inverse()const noexcept
        -> std::enable_if_t<Row2 == Col2,Matrix<Type2,Row2,Col2>>{
            return adjoint() / det();
        }

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


        Matrix<Type,1,Col> row(size_t r)const noexcept{
            return sub<1,Col>(r,0);
        }

        Matrix<Type,Row,1> col(size_t c)const noexcept{
            return sub<Row,1>(0,c);
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


    private:
        std::array<value_type,Count> m_data;
    };

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

#endif