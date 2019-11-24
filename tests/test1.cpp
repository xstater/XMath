#include "XTest/XTest.h"
#include "Matrix.h"
#include "Vector.h"
#include "Quaternion.h"
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
//    INFO("identity:\n",Matrix<double,3,3>().identity());
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

//CASE_BEGIN(test3)
//    using namespace xmath;
//    auto m1 = Vector<float,3>{
//        1,3,5
//    };
//    auto m2 = Vector<float,3>{
//        3,2,1
//    };
//    INFO("[1,3,5] transpose:\n",m1.transpose());
//    INFO("nothing:\n",Vector<float,3>(m1.transpose()));
//    INFO("[1,3,5;3,2,1]:\n",m1.extend<Direction::down>(m2));
//    INFO("[1,3,5] `dot` [3;2;1] = ",m2.dot(m1));
//    INFO("[1,3,5] `cross` [3;2;1] = ",m1.cross(m2));
//    auto m3 = Matrix<float,2,3>{
//        1,2,3,
//        4,5,6
//    };
//    auto m4 = Matrix<float,3,4>{
//        1,2,3,4,
//        5,6,7,8,
//        2,3,4,5
//    };
////    INFO("m3 product m4:\n",m3.product(m4));
//    INFO("m3 product m4:\n",m3 % m4);
//
//    //m3.dot(m2);
//    //m2.dot(m3);
//
//    auto v1 = Matrix<float,1,3>{
//        1,2,3
//    };
//    auto v2 = Matrix<float,3,1>{
//        3,
//        4,
//        5
//    };
//    INFO("v1 * v2:\n",v1 % v2);
//    INFO("v2 * v1:\n",v2 % v1);
//    auto q1 = Vector<float,4>{4,2,1,3};
//    auto q2 = Vector<float,4>{2,2,3,1};
//    INFO("q1 cross q2:\n",q1.cross(q2));
//CASE_END
//
//RUN(test3)

//CASE_BEGIN(test4)
//    using namespace xmath;
//    auto m1 = Matrix<float,1,1>{
//        2
//    };
//    auto m2 = Matrix<float,2,2>{
//        2,2,
//        3,5
//    };
//    auto m3 = Matrix<float,3,3>{
//        2,3,4,
//        1,3,5,
//        3,3,7
//     };
//    auto v3 = Vector3f{
//        1,2,4
//    };
//    auto v4 = Vector3f{
//        1,2,3,
//    };
//    auto m4 = Matrix<float,4,4>{
//        1,3,5,7,
//        7,8,5,3,
//        2,1,2,3,
//        3,3,3,1
//    };
//    INFO("m400\n",m4.cofactor(1,1));
//    INFO("det(m1):\n",m1.det());
//    INFO("det(m2):\n",m2.det());
//    INFO("det(m3):\n",m3.det());
//    INFO("det(m4):\n",m4.det());
//    INFO("adjoint(m4):\n",m4.adjoint());
//    INFO("inverse(m4):\n",m4.inverse());
//    INFO("extend(m3,v3,right):\n",m3.extend(v3.transpose()));
//    INFO("extend(m3,v3,left):\n",m3.extend<Direction::left>(v3.transpose()));
//    INFO("extend(m3,v4,up):\n",m3.extend<Direction::up>(v4));
//    INFO("extend(m3,v4,down):\n",m3.extend<Direction::down>(v4));
//    INFO("length(v3):\n",v3.length());
//    INFO("length2(v3):\n",v3.length2());
//    INFO("normalize(v3):\n",v3.normalize());
//    INFO("row(m4,1):\n",m4.row(1));
//    INFO("col(m4,1):\n",m4.col(1));
//
//    auto v = Vector4d{
//        2,2,2,1
//    };
//    auto id = Matrix4d().identity();
//    auto tl = Vector3d{1,2,3}.translate();
//    auto sc = Vector3d{2,2,2}.scale();
//    INFO("v:\n",v);
//    INFO("tl:\n",tl);
//    INFO("sc:\n",sc);
//    INFO("tl % v:\n",tl % v.transpose());
//    INFO("sc % v:\n",sc % v.transpose());
//    INFO("id:\n",id);
//    INFO("rotm1:\n",Vector3d{0,0,1}.rotate(1));
//    auto q1 = Quaterniond{4,2,1,2};//xyzw
//    auto q2 = Quaterniond{2,2,1,3};//xyzw
//    INFO("q1.normalize():\n",q1.normalize());
//    INFO("q1 cross q2:\n",q1.cross(q2));
//    INFO("q1.conjugate:\n",q1.normalize().conjugate());
//    INFO("q1.inverse:\n",q1.normalize().inverse());
//    INFO("unit quaternion:\n",q1.normalize().cross(q1.normalize().inverse()));
//    INFO("q1.normalize().rotate():\n",q1.normalize().rotate());
//    INFO("from rotation matrix:\n",Quaterniond(q1.normalize().rotate()));
//    INFO("q1:",q1.normalize());
//CASE_END
//
//RUN(test4)

#include <iostream>
#include "XMath.h"

using namespace std;
using namespace xmath;

int main(){
    auto v1 = Vector4f{1,2,3,1};//a 4d float COL vector
    auto t = Vector3f{1,1,1}.translate();//construct a Translation matrix
    v1 = t % v1;//apply to v1 (need to transpose)
    cout << v1 << endl;//[2,3,4,1]
    return 0;
}