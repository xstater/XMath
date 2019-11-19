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

CASE_BEGIN(test2)

CASE_END

RUN(test2)