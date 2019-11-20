#ifndef _XMATH_HELPER_H_
#define _XMATH_HELPER_H_

namespace xmath{
    ///implement
    namespace detail{
        ///is_scalar
        template <size_t Row,size_t Col>
        struct is_scalar{
            enum{ value = false };
        };
        template <>
        struct is_scalar<1,1>{
            enum{ value = true };
        };

        ///is_row_vector
        template <size_t Row,size_t Col>
        struct is_row_vector{
            enum{ value = false };
        };
        template <size_t Col>
        struct is_row_vector<1,Col>{
            enum{ value = true };
        };
        template <>
        struct is_row_vector<1,1>{
            enum{ value = true };
        };

        ///is_col_vector
        template <size_t Row,size_t Col>
        struct is_col_vector{
            enum{ value = false };
        };
        template <size_t Row>
        struct is_col_vector<Row,1>{
            enum{ value = true };
        };
        template <>
        struct is_col_vector<1,1>{
            enum{ value = true };
        };

        ///get_vector_length
        template <size_t Row,size_t Col>
        struct get_vector_length{
            enum{ value = 0 };
        };
        template <size_t Row>
        struct get_vector_length<Row,1>{
            enum{ value = Row };
        };
        template <size_t Col>
        struct get_vector_length<1,Col>{
            enum{ value = Col };
        };
        template <>
        struct get_vector_length<1,1>{
            enum{ value = 1 };
        };

        ///is_vector
        template <size_t Row,size_t Col>
        struct is_vector{
            enum{ value = false };
        };
        template <size_t Row>
        struct is_vector<Row,1>{
            enum{ value = true };
        };
        template <size_t Col>
        struct is_vector<1,Col>{
            enum{ value = true };
        };
        template <>
        struct is_vector<1,1>{
            enum{ value = true };
        };

        ///is_square_matrix
        template <size_t Row,size_t Col>
        struct is_square_matrix{
            enum{ value = false };
        };
        template <size_t Row>
        struct is_square_matrix<Row,Row>{
            enum{ value = true };
        };
    }

    ///interfaces
    template <size_t Row,size_t Col>
    using is_scalar = detail::is_scalar<Row,Col>;
    template <size_t Row,size_t Col>
    constexpr bool is_scalar_v = detail::is_scalar<Row,Col>::value;

    template <size_t Row,size_t Col>
    using is_row_vector = detail::is_row_vector<Row,Col>;
    template <size_t Row,size_t Col>
    constexpr bool is_row_vector_v = detail::is_row_vector<Row,Col>::value;

    template <size_t Row,size_t Col>
    using is_col_vector = detail::is_col_vector<Row,Col>;
    template <size_t Row,size_t Col>
    constexpr bool is_col_vector_v = detail::is_col_vector<Row,Col>::value;

    template <size_t Row,size_t Col>
    using is_vector = detail::is_vector<Row,Col>;
    template <size_t Row,size_t Col>
    constexpr bool is_vector_v = detail::is_vector<Row,Col>::value;

    template <size_t Row,size_t Col>
    using get_vector_length = detail::get_vector_length<Row,Col>;
    template <size_t Row,size_t Col>
    constexpr size_t get_vector_length_v = detail::get_vector_length<Row,Col>::value;

    template <size_t Row,size_t Col>
    using is_square_matrix = detail::is_square_matrix<Row,Col>;
    template <size_t Row,size_t Col>
    constexpr bool is_square_matrix_v = detail::is_square_matrix<Row,Col>::value;
}

#endif //_XMATH_HELPER_H_