#ifndef _XMATH_VECTOR_H_
#define _XMATH_VECTOR_H_

#include <fstream>
#include <initializer_list>
#include <math.h>

#define XMATH_MIN 0.0000001

namespace xmath{

    template <class Type>
    constexpr Type _abs(Type a){
        return a<0?-a:a;
    }

    template <class Type>
    constexpr bool float_equal(Type a,Type b){
        return _abs(a - b) < XMATH_MIN;
    }

    template <class Type>
    class Vector2d{
    public:
        union {
            Type x;
            Type s;
        };
        union {
            Type y;
            Type t;
        };

        explicit Vector2d(Type dx,Type dy)
            :x(dx),y(dy){}
        Vector2d(const Type *ptr)
            :x(ptr[0]),y(ptr[1]){}
        Vector2d(const std::initializer_list<Type> &ilist)
            :x(ilist.begin()[0]),y(ilist.begin()[1]){}
        template <class Type2>
        Vector2d(const Vector2d<Type2> &v)
            :x(v.x),y(v.y){}
        Vector2d(const Vector2d<Type> &) = default;
        Vector2d(Vector2d<Type> &&) = default;
        ~Vector2d() = default;

        Vector2d<Type> &operator=(const Vector2d<Type> &) = default;
        Vector2d<Type> &operator=(Vector2d<Type> &&) = default;

        operator Type*()noexcept{
            return &x;
        }
        operator const Type*()const noexcept{
            return &x;
        }

        Type &operator[](int index)noexcept{
            return (&x)[index];
        }
        const Type &operator[](int index)const noexcept{
            return (&x)[index];
        }

        Vector2d<Type> operator+(const Vector2d<Type> &vec)const noexcept{
            return Vector2d<Type>(this->x + vec.x,this->y + vec.y);
        }
        Vector2d<Type> operator-(const Vector2d<Type> &vec)const noexcept{
            return Vector2d<Type>(this->x - vec.x,this->y - vec.y);
        }
        Vector2d<Type> operator*(const Vector2d<Type> &vec)const noexcept{
            return Vector2d<Type>(this->x * vec.x,this->y * vec.y);
        }
        Vector2d<Type> operator/(const Vector2d<Type> &vec)const noexcept{
            return Vector2d<Type>(this->x / vec.x,this->y / vec.y);
        }

        Vector2d<Type> operator+(Type t)const noexcept{
            return Vector2d<Type>(this->x + t,this->y + t);
        }
        Vector2d<Type> operator-(Type t)const noexcept{
            return Vector2d<Type>(this->x - t,this->y - t);
        }
        Vector2d<Type> operator*(Type t)const noexcept{
            return Vector2d<Type>(this->x * t,this->y * t);
        }
        Vector2d<Type> operator/(Type t)const noexcept{
            return Vector2d<Type>(this->x / t,this->y / t);
        }
        Vector2d<Type> operator-()const noexcept{
            return Vector2d<Type>(-x,-y);
        }

        Vector2d<Type> &operator+=(const Vector2d<Type> &vec) noexcept{
            this->x += vec.x;
            this->y += vec.y;
            return *this;
        }
        Vector2d<Type> &operator-=(const Vector2d<Type> &vec) noexcept{
            this->x -= vec.x;
            this->y -= vec.y;
            return *this;
        }
        Vector2d<Type> &operator*=(const Vector2d<Type> &vec) noexcept{
            this->x *= vec.x;
            this->y *= vec.y;
            return *this;
        }
        Vector2d<Type> &operator/=(const Vector2d<Type> &vec) noexcept{
            this->x /= vec.x;
            this->y /= vec.y;
            return *this;
        }

        Vector2d<Type> &operator+=(Type t) noexcept{
            this->x += t;
            this->y += t;
            return *this;
        }
        Vector2d<Type> &operator-=(Type t) noexcept{
            this->x -= t;
            this->y -= t;
            return *this;
        }
        Vector2d<Type> &operator*=(Type t) noexcept{
            this->x *= t;
            this->y *= t;
            return *this;
        }
        Vector2d<Type> &operator/=(Type t) noexcept{
            this->x /= t;
            this->y /= t;
            return *this;
        }

        bool operator==(const Vector2d<Type> &v)const noexcept{
            return float_equal(this->x,v.x)&&float_equal(this->y,v.y);
        }
        bool operator!=(const Vector2d<Type> &v)const noexcept{
            return !(*this == v);
        }

        Type dot(const Vector2d<Type> &vec)const noexcept{
            return x * vec.x + y * vec.y;
        }

        friend Type dot(const Vector2d<Type> &vec1,const Vector2d<Type> &vec2)noexcept{
            return vec1.x * vec2.x + vec1.y * vec2.y;
        }

        int length()const noexcept{
            return sqrt<Type>(x * x + y * y);
        }
        int length2()const noexcept{
            return x * x + y * y;
        }

        friend std::ostream &operator<<(std::ostream &out,const Vector2d<Type> &v){
            return out<<v.x<<' '<<v.y;
        }

    protected:
    private:
    };

    template <class Type>
    class Vector3d{
    public:
        union {
            Type x;
            Type s;
            Type r;
        };
        union {
            Type y;
            Type t;
            Type g;
        };
        union {
            Type z;
            Type u;
            Type b;
        };

        explicit Vector3d(Type dx,Type dy,Type dz)
                :x(dx),y(dy),z(dz){}
        Vector3d(const Type *ptr)
                :x(ptr[0]),y(ptr[1]),z(ptr[2]){}
        Vector3d(const std::initializer_list<Type> &ilist)
                :x(ilist.begin()[0]),y(ilist.begin()[1]),z(ilist.begin()[2]){}
        template <class Type2>
        Vector3d(const Vector3d<Type2> &v)
                :x(v.x),y(v.y),z(v.z){}
        Vector3d(const Vector3d<Type> &) = default;
        Vector3d(Vector3d<Type> &&) = default;
        ~Vector3d() = default;

        Vector3d<Type> &operator=(const Vector3d<Type> &) = default;
        Vector3d<Type> &operator=(Vector3d<Type> &&) = default;

        operator Type*()noexcept{
            return &x;
        }
        operator const Type*()const noexcept{
            return &x;
        }

        Type &operator[](int index)noexcept{
            return (&x)[index];
        }
        const Type &operator[](int index)const noexcept{
            return (&x)[index];
        }

        Vector3d<Type> operator+(const Vector3d<Type> &vec)const noexcept{
            return Vector3d<Type>(this->x + vec.x,this->y + vec.y,this->z + vec.z);
        }
        Vector3d<Type> operator-(const Vector3d<Type> &vec)const noexcept{
            return Vector3d<Type>(this->x - vec.x,this->y - vec.y,this->z - vec.z);
        }
        Vector3d<Type> operator*(const Vector3d<Type> &vec)const noexcept{
            return Vector3d<Type>(this->x * vec.x,this->y * vec.y,this->z * vec.z);
        }
        Vector3d<Type> operator/(const Vector3d<Type> &vec)const noexcept{
            return Vector3d<Type>(this->x / vec.x,this->y / vec.y,this->z / vec.z);
        }

        Vector3d<Type> operator+(Type t)const noexcept{
            return Vector3d<Type>(this->x + t,this->y + t,this->z + t);
        }
        Vector3d<Type> operator-(Type t)const noexcept{
            return Vector3d<Type>(this->x - t,this->y - t,this->z - t);
        }
        Vector3d<Type> operator*(Type t)const noexcept{
            return Vector3d<Type>(this->x * t,this->y * t,this->z * t);
        }
        Vector3d<Type> operator/(Type t)const noexcept{
            return Vector3d<Type>(this->x / t,this->y / t,this->z / t);
        }
        Vector3d<Type> operator-()const noexcept{
            return Vector3d<Type>(-x,-y,-z);
        }

        Vector3d<Type> &operator+=(const Vector3d<Type> &vec) noexcept{
            this->x += vec.x;
            this->y += vec.y;
            this->z += vec.z;
            return *this;
        }
        Vector3d<Type> &operator-=(const Vector3d<Type> &vec) noexcept{
            this->x -= vec.x;
            this->y -= vec.y;
            this->z -= vec.z;
            return *this;
        }
        Vector3d<Type> &operator*=(const Vector3d<Type> &vec) noexcept{
            this->x *= vec.x;
            this->y *= vec.y;
            this->z *= vec.z;
            return *this;
        }
        Vector3d<Type> &operator/=(const Vector3d<Type> &vec) noexcept{
            this->x /= vec.x;
            this->y /= vec.y;
            this->z /= vec.z;
            return *this;
        }

        Vector3d<Type> &operator+=(Type t) noexcept{
            this->x += t;
            this->y += t;
            this->z += t;
            return *this;
        }
        Vector3d<Type> &operator-=(Type t) noexcept{
            this->x -= t;
            this->y -= t;
            this->z -= t;
            return *this;
        }
        Vector3d<Type> &operator*=(Type t) noexcept{
            this->x *= t;
            this->y *= t;
            this->z *= t;
            return *this;
        }
        Vector3d<Type> &operator/=(Type t) noexcept{
            this->x /= t;
            this->y /= t;
            this->z /= t;
            return *this;
        }

        bool operator==(const Vector3d<Type> &v)const noexcept{
            return float_equal(this->x,v.x)&&float_equal(this->y,v.y)&&float_equal(this->z,v.z);
        }
        bool operator!=(const Vector3d<Type> &v)const noexcept{
            return !(*this == v);
        }

        Type dot(const Vector3d<Type> &vec)const noexcept{
            return x * vec.x + y * vec.y + z * vec.z;
        }
        friend Type dot(const Vector3d<Type> &vec1,const Vector3d<Type> &vec2)noexcept{
            return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
        }

        Vector3d<Type> cross(const Vector3d<Type> &vec)const noexcept{
            return Vector3d<Type>(this->y * vec.z - this->z * vec.y,
                                   this->z * vec.x - this->x * vec.z,
                                   this->x * vec.y - this->y * vec.x);
        }
        friend Vector3d<Type> cross(const Vector3d<Type> &vec1,const Vector3d<Type> &vec2)noexcept{
            return Vector3d<Type>(vec1.y * vec2.z - vec1.z * vec2.y,
                                  vec1.z * vec2.x - vec1.x * vec2.z,
                                  vec1.x * vec2.y - vec1.y * vec2.x);
        }

        int length()const noexcept{
            return sqrt<Type>(x * x + y * y + z * z);
        }
        int length2()const noexcept{
            return x * x + y * y+ z * z;
        }

        friend std::ostream &operator<<(std::ostream &out,const Vector3d<Type> &v){
            return out<<v.x<<' '<<v.y<<' '<<v.z;
        }

    protected:
    private:
    };

    template <class Type>
    class Vector4d{
    public:
        union {
            Type x;
            Type s;
            Type r;
        };
        union {
            Type y;
            Type t;
            Type g;
        };
        union {
            Type z;
            Type u;
            Type b;
        };
        union {
            Type w;
            Type v;
            Type a;
        };

        explicit Vector4d(Type dx,Type dy,Type dz,Type dw)
                :x(dx),y(dy),z(dz),w(dw){}
        Vector4d(const Type *ptr)
                :x(ptr[0]),y(ptr[1]),z(ptr[2]),w(ptr[3]){}
        Vector4d(const std::initializer_list<Type> &ilist)
                :x(ilist.begin()[0]),y(ilist.begin()[1]),z(ilist.begin()[2]),w(ilist.begin()[3]){}
        template <class Type2>
        Vector4d(const Vector4d<Type2> &vec)
                :x(vec.x),y(vec.y),z(vec.z),w(vec.w){}
        Vector4d(const Vector4d<Type> &) = default;
        Vector4d(Vector4d<Type> &&) = default;
        ~Vector4d() = default;

        Vector4d<Type> &operator=(const Vector4d<Type> &) = default;
        Vector4d<Type> &operator=(Vector4d<Type> &&) = default;

        operator Type*()noexcept{
            return &x;
        }
        operator const Type*()const noexcept{
            return &x;
        }

        Type &operator[](int index)noexcept{
            return (&x)[index];
        }
        const Type &operator[](int index)const noexcept{
            return (&x)[index];
        }

        Vector4d<Type> operator+(const Vector4d<Type> &vec)const noexcept{
            return Vector4d<Type>(this->x + vec.x,this->y + vec.y,this->z + vec.z,this->w + vec.w);
        }
        Vector4d<Type> operator-(const Vector4d<Type> &vec)const noexcept{
            return Vector4d<Type>(this->x - vec.x,this->y - vec.y,this->z - vec.z,this->w - vec.w);
        }
        Vector4d<Type> operator*(const Vector4d<Type> &vec)const noexcept{
            return Vector4d<Type>(this->x * vec.x,this->y * vec.y,this->z * vec.z,this->w * vec.w);
        }
        Vector4d<Type> operator/(const Vector4d<Type> &vec)const noexcept{
            return Vector4d<Type>(this->x / vec.x,this->y / vec.y,this->z / vec.z,this->w / vec.w);
        }

        Vector4d<Type> operator+(Type t)const noexcept{
            return Vector4d<Type>(this->x + t,this->y + t,this->z + t,this->w + t);
        }
        Vector4d<Type> operator-(Type t)const noexcept{
            return Vector4d<Type>(this->x - t,this->y - t,this->z - t,this->w - t);
        }
        Vector4d<Type> operator*(Type t)const noexcept{
            return Vector4d<Type>(this->x * t,this->y * t,this->z * t,this->w * t);
        }
        Vector4d<Type> operator/(Type t)const noexcept{
            return Vector4d<Type>(this->x / t,this->y / t,this->z / t,this->w / t);
        }
        Vector4d<Type> operator-()const noexcept{
            return Vector4d<Type>(-x,-y,-z,-w);
        }

        Vector4d<Type> &operator+=(const Vector4d<Type> &vec) noexcept{
            this->x += vec.x;
            this->y += vec.y;
            this->z += vec.z;
            this->w += vec.w;
            return *this;
        }
        Vector4d<Type> &operator-=(const Vector4d<Type> &vec) noexcept{
            this->x -= vec.x;
            this->y -= vec.y;
            this->z -= vec.z;
            this->w -= vec.w;
            return *this;
        }
        Vector4d<Type> &operator*=(const Vector4d<Type> &vec) noexcept{
            this->x *= vec.x;
            this->y *= vec.y;
            this->z *= vec.z;
            this->w *= vec.w;
            return *this;
        }
        Vector4d<Type> &operator/=(const Vector4d<Type> &vec) noexcept{
            this->x /= vec.x;
            this->y /= vec.y;
            this->z /= vec.z;
            this->w /= vec.w;
            return *this;
        }

        Vector4d<Type> &operator+=(Type t) noexcept{
            this->x += t;
            this->y += t;
            this->z += t;
            this->w += t;
            return *this;
        }
        Vector4d<Type> &operator-=(Type t) noexcept{
            this->x -= t;
            this->y -= t;
            this->z -= t;
            this->w -= t;
            return *this;
        }
        Vector4d<Type> &operator*=(Type t) noexcept{
            this->x *= t;
            this->y *= t;
            this->z *= t;
            this->w *= t;
            return *this;
        }
        Vector4d<Type> &operator/=(Type t) noexcept{
            this->x /= t;
            this->y /= t;
            this->z /= t;
            this->w /= t;
            return *this;
        }

        bool operator==(const Vector4d<Type> &vec)const noexcept{
            return float_equal(this->x,vec.x)&&float_equal(this->y,vec.y)&&float_equal(this->z,vec.z)&&float_equal(this->w,vec.w);
        }
        bool operator!=(const Vector4d<Type> &vec)const noexcept{
            return !(*this == vec);
        }

        Type dot(const Vector4d<Type> &vec)const noexcept{
            return x * vec.x + y * vec.y + z * vec.z + w * vec.w;
        }
        friend Type dot(const Vector4d<Type> &vec1,const Vector4d<Type> &vec2)noexcept{
            return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z + vec1.w * vec2.w;
        }

        int length()const noexcept{
            return sqrt<Type>(x * x + y * y + z * z + w * w);
        }
        int length2()const noexcept{
            return x * x + y * y+ z * z + w * w;
        }

        friend std::ostream &operator<<(std::ostream &out,const Vector4d<Type> &v){
            return out<<v.x<<' '<<v.y<<' '<<v.z<<' '<<v.w;
        }

    protected:
    private:
    };


    using Vector2df = Vector2d<float>;
    using Vector2dd = Vector2d<double>;
    using Vector2di = Vector2d<int>;

    using Vector3df = Vector3d<float>;
    using Vector3dd = Vector3d<double>;
    using Vector3di = Vector3d<int>;

    using Vector4df = Vector4d<float>;
    using Vector4dd = Vector4d<double>;
    using Vector4di = Vector4d<int>;
}

#undef XMATH_MIN

#endif //_XMATH_VECTOR_H_
