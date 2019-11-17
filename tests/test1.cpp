#include "XTest/XTest.h"
#include "Matrix.h"

CASE_BEGIN(test1)
    using namespace xmath;
    Matrix<int,12,2> m1;
//    Matrix<int,2,12> m2(m1);
    INFO('\n',m1);
CASE_END

RUN(test1)