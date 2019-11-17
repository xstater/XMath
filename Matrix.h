#ifndef _XMATH_MATRIX_H_
#define _XMATH_MATRIX_H_

#include <cctype>
#include <array>

namespace xmath{
    template <class Type,size_t N,size_t M>
    class Matrix{
    public:
        using value_type = Type;
        static constexpr size_t row = N;
        static constexpr size_t col = M;
        static constexpr size_t mat_count = N * M;

        /** @name Default Constructor
         *  @brief construct a zero matrix
         */
        Matrix(){
            for(auto &itr : m_data){
                itr = 0;
            }
        }
        /** @name Copy Constructor
         *  @param mat the source of copy
         *  @brief copy from another matrix whose size equal this one
         */
        template <class Type2,size_t N2,size_t M2>
        Matrix(const Matrix<Type2,N2,M2> &mat){
            static_assert(N2*M2 == mat_count,"Cannot copy cause the size must be equal");
            for(auto itr1 = m_data.begin(),itr2 = mat.m_data.begin();
                itr1 != m_data.end() && itr2 != mat.m_data.end();
                ++itr1,++itr2){
                *itr1 = *itr2;
            }
        }
        ~Matrix() = default;

        friend std::ostream &operator<<(std::ostream &os,const Matrix &mat){
            for(int i = 0;i < M;++i){
                os << '[';
                for(int j = 0;j < N - 1;++j){
                    os << mat.m_data[i*M+j] << ',';
                }
                os << mat.m_data[i*M+(N-1)] << "]\n";
            }
            return os;
        }
    protected:
    private:
        std::array<value_type,mat_count> m_data;
    };
}

#endif //_XMATH_MATRIX_H_