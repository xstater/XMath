#include "XTest/XTest.h"
#include "Matrix.h"
#include "Vector.h"
#include "Quaternion.h"

#define VMATH_NAMESPACE vmath
#include <vmath.h>

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
//    INFO("[1,3,5;3,2,1]:\n",m1.toRow().extend<Direction::down>(m2.toRow()));
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
//    auto q1 = Vector<float,3>{4,2,1};
//    auto q2 = Vector<float,3>{2,2,3};
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
//    INFO("extend(m3,v3,right):\n",m3.extend(v3.toCol()));
//    INFO("extend(m3,v3,left):\n",m3.extend<Direction::left>(v3.toCol()));
//    INFO("extend(m3,v4,up):\n",m3.extend<Direction::up>(v4.toRow()));
//    INFO("extend(m3,v4,down):\n",m3.extend<Direction::down>(v4.toRow()));
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
//    INFO("tl % v:\n",tl % v);
//    INFO("sc % v:\n",sc % v);
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

CASE_BEGIN(vmath_comp)
    auto x_model =
            xmath::Vector3d{2.2,3.3,4.4}.translate()
//          % xmath::Vector3d{1.3,2.4,6.6}.rotate()
          % xmath::Vector3d{1,2,1}.scale();
    auto x_vec = xmath::Vector4d{1.3,3.4,2.1,1.0};
    auto v_model =
            vmath::Matrix4d::createTranslation(2.2,3.3,4.4)
//          * vmath::Matrix4d::createRotationAroundAxis(1.3,2.4,6.6)
          * vmath::Matrix4d::createScale(1,2,1);
    auto v_vec = vmath::Vector4d{1.3,3.4,2.1,1.0};

    INFO("xmath:",x_model % x_vec);
    INFO("vmath:",v_model * v_vec);

    INFO("r1:\n",vmath::Matrix4d::createRotationAroundAxis(23,33,41));//deg
    INFO("r2:\n",xmath::Vector3d{0.401426,0.575959,0.715585}.rotate());//rad
//    INFO("r1:\n",vmath::Matrix4d::createRotationAroundAxis(45,0,0));//deg
//    INFO("r2:\n",xmath::Vector3d{0.7825398,0,0}.rotate());//rad

    INFO("x-lookAt:\n",
            xmath::Vector3d{1,1,1}.lookAt(xmath::Vector3d{0.5,0.5,0.5},xmath::Vector3d{0,1,0}));
    INFO("v-lookAt:\n",
            vmath::Matrix4d::createLookAt(
                    vmath::Vector3d(1,1,1),
                    vmath::Vector3d(0.5,0.5,0.5),
                    vmath::Vector3d(0,1,0)));

    INFO("x-frustum:\n",
            xmath::Vector<double,6>{6,-6,-6,6,2,3}.frustum());
    INFO("v-frustum:\n",
            vmath::Matrix4d::createFrustum(-6,6,-6,6,2,3));
    INFO("x-fov:\n",xmath::Vector4d{1.0,2.0 * std::atan(3.0),2,3}.frustum());

    INFO("x-ortho:\n",
            xmath::Vector<double,6>{7,-7,-6,6,-4,4}.ortho());
    INFO("v-ortho:\n",
            vmath::Matrix4d::createOrtho(-6,6,-7,7,-4,4));

    INFO("x-quat-rotmatrix:\n",
            xmath::Quaterniond{2,3,4,1}.rotate());
    INFO("v-quat-rotmatrix:\n",
            vmath::Quaternion<double>(1,2,3,4).transform());
CASE_END

RUN(vmath_comp)


