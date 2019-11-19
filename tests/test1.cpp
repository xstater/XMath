#include "XTest/XTest.h"
#include "Matrix.h"
#include <xmmintrin.h>

//CASE_BEGIN(test1)
//    using namespace xmath;
//    Matrix<int,2,3> m1({
//        1,2,3,
//        4,5,6
//    });
////    static_cast<int*>(m1)[2] = 3;
////    m1[2] = 3;
//    auto m2 = Matrix<int,2,3>(static_cast<int *>(m1));
//    std::array<int,3> s1 = {1,2,3};
//    auto m3 = Matrix<int,1,3>(s1.begin(),s1.end());
//    auto m4 = Matrix<int,2,3>({
//        1,2,3,
//        4,5,6
//    });
//    auto m5 = Matrix<int,3,2>(m4);
//    INFO("m1:\n",m1);
//    INFO("m2:\n",m2);
//    INFO("m1+m2:\n",m1 + m2);
//    INFO("m1-m2:\n",m1 - m2);
//    INFO("m1*m2:\n",m1 * m2);
//    INFO("m1/m2:\n",m1 / m2);
//    INFO("m3:\n",m3);
//    INFO("m4:\n",m4);
//    INFO("m5:\n",m5);
//    m5 = {
//        4,5,
//        2,3,
//        1,3
//    };
//    INFO("m5:\n",m5);
//    INFO("m4:\n",m4 = m5);
//    INFO("identity:\n",Matrix<float,3,3>::createIdentity());
//CASE_END
//
//RUN(test1)

//CASE_BEGIN(test2)
//    using namespace xmath;
//    auto m1 = Matrix<float,2,3>{
//        1,2,3,
//        4,5,6
//    };
//    m1 *= Matrix<float,2,3>{
//        2,3,4,
//        1,3,1
//    };
//    INFO("m1:\n",m1);
//    INFO("transpose(m1):\n",/*m1.transpose()*/~m1);
//    INFO("sub matrix:\n",m1.sub<2,2>(0,0));
//
//    INFO("is_vector<1,4>:",xmath::is_vector_v<1,4>);
//    INFO("is_vector<6,1>:",xmath::is_vector_v<6,1>);
//    INFO("is_vector<2,3>:",xmath::is_vector_v<2,3>);
//    INFO("is_scalar<1,1>:",xmath::is_scalar_v<1,1>);
//    INFO("is_square<3,3>:",xmath::is_square_matrix_v<3,3>);
//CASE_END
//
//RUN(test2)

CASE_BEGIN(test3)
    using namespace xmath;
    auto m1 = Matrix<float,1,3>({
        1,3,5
    });
    auto m2 = Matrix<float,3,1>({
        3,
        2,
        1
    });
    INFO("[1,3,5] `dot` [3;2;1] = ",m2.dot(m1));
    INFO("[1,3,5] `cross` [3;2;1] = ",m1.cross(m2));
    auto m3 = Matrix<float,2,3>({
        1,2,3,
        4,5,6
    });
    auto m4 = Matrix<float,3,4>({
        1,2,3,4,
        5,6,7,8,
        2,3,4,5
    });
//    INFO("m3 product m4:\n",m3.product(m4));
    INFO("m3 product m4:\n",m3 & m4);

    //m3.dot(m2);
    //m2.dot(m3);
CASE_END



RUN(test3)