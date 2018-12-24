#ifndef _XMATH_VECTOR_H_
#define _XMATH_VECTOR_H_

#include <ios>
#include <cmath>

namespace xmath{
    template<class Type>
    class Vector2d{
    public:
        union{
            Type x;
            Type r;
            Type u;
        };
        union{
            Type y;
            Type g;
            Type v;
        };

        Vector2d()
                :x(0),y(0){}
        Vector2d(Type dx,Type dy,Type dz)
                :x(dx),y(dy){}
        template<class Type2>
        Vector2d(const Vector2d<Type2> &vec)
                :x(static_cast<Type>(vec.x)),
                 y(static_cast<Type>(vec.y)){}
        ~Vector2d() = default;

        template<class Type2>
        Vector2d &operator=(const Vector2d<Type2> &vec){
            x = static_cast<Type>(vec.x);
            y = static_cast<Type>(vec.y);
            return *this;
        }

        const Type &operator[](int index)const noexcept{
            return *(&x + index);
        }
        Type &operator[](int index) noexcept{
            return *(&x + index);
        }

        operator Type*()noexcept{
            return reinterpret_cast<Type>(this);
        }
        operator const Type*()const noexcept{
            return reinterpret_cast<Type>(this);
        }

        Vector2d operator+(const Vector2d &rhs)const noexcept{
            return Vector2d(x + rhs.x,y + rhs.y);
        }
        Vector2d operator-(const Vector2d &rhs)const noexcept{
            return Vector2d(x - rhs.x,y - rhs.y);
        }
        Vector2d operator*(const Vector2d &rhs)const noexcept{
            return Vector2d(x * rhs.x,y * rhs.y);
        }
        Vector2d operator/(const Vector2d &rhs)const noexcept{
            return Vector2d(x / rhs.x,y / rhs.y);
        }

        Vector2d operator+(const Type &rhs)const noexcept{
            return Vector2d(x + rhs,y + rhs);
        }
        Vector2d operator-(const Type &rhs)const noexcept{
            return Vector2d(x - rhs,y - rhs);
        }
        Vector2d operator*(const Type &rhs)const noexcept{
            return Vector2d(x * rhs,y * rhs);
        }
        Vector2d operator/(const Type &rhs)const noexcept{
            return Vector2d(x / rhs,y / rhs);
        }


        Vector2d &operator+=(const Vector2d &rhs)noexcept{
            x += rhs.x;
            y += rhs.y;
            return *this;
        }
        Vector2d &operator-=(const Vector2d &rhs)noexcept{
            x -= rhs.x;
            y -= rhs.y;
            return *this;
        }
        Vector2d &operator*=(const Vector2d &rhs)noexcept{
            x *= rhs.x;
            y *= rhs.y;
            return *this;
        }
        Vector2d &operator/=(const Vector2d &rhs)noexcept{
            x /= rhs.x;
            y /= rhs.y;
            return *this;
        }

        Vector2d &operator+=(const Type &rhs)noexcept{
            x += rhs;
            y += rhs;
            return *this;
        }
        Vector2d &operator-=(const Type &rhs)noexcept{
            x -= rhs;
            y -= rhs;
            return *this;
        }
        Vector2d &operator*=(const Type &rhs)noexcept{
            x *= rhs;
            y *= rhs;
            return *this;
        }
        Vector2d &operator/=(const Type &rhs)noexcept{
            x /= rhs;
            y /= rhs;
            return *this;
        }

        Vector2d operator-()const noexcept{
            return Vector2d(-x,-y);
        }

        Type length()const noexcept{
            return std::sqrt(x * x + y * y);
        }

        Type length2()const noexcept{
            return x * x + y * y;
        }

        Vector2d &normalize()noexcept{
            *this /= length();
            return *this;
        }

        Type dot(const Vector2d &vec)const noexcept{
            return x * vec.x + y * vec.y;
        }

        friend std::ostream &operator<<(std::ostream &os,const Vector2d<Type> &rhs){
            os<<'['<<rhs.x<<','<<rhs.y<<']';
            return os;
        }
    protected:
    private:
    };

    template<class Type>
    class Vector3d{
    public:
        union{
            Type x;
            Type r;
            Type u;
        };
        union{
            Type y;
            Type g;
            Type v;
        };
        union{
            Type z;
            Type b;
            Type s;
        };

        Vector3d()
            :x(0),y(0),z(0){}
        Vector3d(Type dx,Type dy,Type dz)
            :x(dx),y(dy),z(dz){}
        template<class Type2>
        Vector3d(const Vector3d<Type2> &vec)
            :x(static_cast<Type>(vec.x)),
             y(static_cast<Type>(vec.y)),
             z(static_cast<Type>(vec.z)){}
        ~Vector3d() = default;

        template<class Type2>
        Vector3d &operator=(const Vector3d<Type2> &vec){
            x = static_cast<Type>(vec.x);
            y = static_cast<Type>(vec.y);
            z = static_cast<Type>(vec.z);
            return *this;
        }

        const Type &operator[](int index)const noexcept{
            return *(&x + index);
        }
        Type &operator[](int index) noexcept{
            return *(&x + index);
        }

        operator Type*()noexcept{
            return reinterpret_cast<Type>(this);
        }
        operator const Type*()const noexcept{
            return reinterpret_cast<Type>(this);
        }

        Vector3d operator+(const Vector3d &rhs)const noexcept{
            return Vector3d(x + rhs.x,y + rhs.y,z + rhs.z);
        }
        Vector3d operator-(const Vector3d &rhs)const noexcept{
            return Vector3d(x - rhs.x,y - rhs.y,z - rhs.z);
        }
        Vector3d operator*(const Vector3d &rhs)const noexcept{
            return Vector3d(x * rhs.x,y * rhs.y,z * rhs.z);
        }
        Vector3d operator/(const Vector3d &rhs)const noexcept{
            return Vector3d(x / rhs.x,y / rhs.y,z / rhs.z);
        }

        Vector3d operator+(const Type &rhs)const noexcept{
            return Vector3d(x + rhs,y + rhs,z + rhs);
        }
        Vector3d operator-(const Type &rhs)const noexcept{
            return Vector3d(x - rhs,y - rhs,z - rhs);
        }
        Vector3d operator*(const Type &rhs)const noexcept{
            return Vector3d(x * rhs,y * rhs,z * rhs);
        }
        Vector3d operator/(const Type &rhs)const noexcept{
            return Vector3d(x / rhs,y / rhs,z / rhs);
        }


        Vector3d &operator+=(const Vector3d &rhs)noexcept{
            x += rhs.x;
            y += rhs.y;
            z += rhs.z;
            return *this;
        }
        Vector3d &operator-=(const Vector3d &rhs)noexcept{
            x -= rhs.x;
            y -= rhs.y;
            z -= rhs.z;
            return *this;
        }
        Vector3d &operator*=(const Vector3d &rhs)noexcept{
            x *= rhs.x;
            y *= rhs.y;
            z *= rhs.z;
            return *this;
        }
        Vector3d &operator/=(const Vector3d &rhs)noexcept{
            x /= rhs.x;
            y /= rhs.y;
            z /= rhs.z;
            return *this;
        }

        Vector3d &operator+=(const Type &rhs)noexcept{
            x += rhs;
            y += rhs;
            z += rhs;
            return *this;
        }
        Vector3d &operator-=(const Type &rhs)noexcept{
            x -= rhs;
            y -= rhs;
            z -= rhs;
            return *this;
        }
        Vector3d &operator*=(const Type &rhs)noexcept{
            x *= rhs;
            y *= rhs;
            z *= rhs;
            return *this;
        }
        Vector3d &operator/=(const Type &rhs)noexcept{
            x /= rhs;
            y /= rhs;
            z /= rhs;
            return *this;
        }

        Vector3d operator-()const noexcept{
            return Vector3d(-x,-y,-z);
        }

        Type length()const noexcept{
            return std::sqrt(x * x + y * y + z * z);
        }

        Type length2()const noexcept{
            return x * x + y * y + z * z;
        }

        Vector3d &normalize()noexcept{
            *this /= length();
            return *this;
        }

        Type dot(const Vector3d &vec)const noexcept{
            return x * vec.x + y * vec.y + z * vec.z;
        }
        Vector3d cross(const Vector3d &vec)const noexcept{
            return Vector3d(y * vec.z - vec.y * z, z * vec.x - vec.z * x, x * vec.y - vec.x * y);
        }

        friend std::ostream &operator<<(std::ostream &os,const Vector3d<Type> &rhs){
            os<<'['<<rhs.x<<','<<rhs.y<<','<<rhs.z<<']';
            return os;
        }
    protected:
    private:
    };

    template<class Type>
    class Vector4d{
    public:
        union{
            Type x;
            Type r;
            Type u;
        };
        union{
            Type y;
            Type g;
            Type v;
        };
        union{
            Type z;
            Type b;
            Type s;
        };
        union{
            Type w;
            Type a;
            Type t;
        };

        Vector4d()
                :x(0),y(0),z(0),w(0){}
        Vector4d(Type dx,Type dy,Type dz,Type dw)
                :x(dx),y(dy),z(dz),w(dw){}
        template<class Type2>
        Vector4d(const Vector4d<Type2> &vec)
                :x(static_cast<Type>(vec.x)),
                 y(static_cast<Type>(vec.y)),
                 z(static_cast<Type>(vec.z)),
                 w(static_cast<Type>(vec.w)){}
        template <class Type2>
        Vector4d(const Vector3d<Type2> &vec3,Type2 dw)
            :x(static_cast<Type>(vec3.x)),
             y(static_cast<Type>(vec3.y)),
             z(static_cast<Type>(vec3.z)),
             w(static_cast<Type>(dw)){}
        ~Vector4d() = default;

        template<class Type2>
        Vector4d &operator=(const Vector4d<Type2> &vec){
            x = static_cast<Type>(vec.x);
            y = static_cast<Type>(vec.y);
            z = static_cast<Type>(vec.z);
            w = static_cast<Type>(vec.w);
            return *this;
        }

        const Type &operator[](int index)const noexcept{
            return *(&x + index);
        }
        Type &operator[](int index) noexcept{
            return *(&x + index);
        }

        operator Type*()noexcept{
            return reinterpret_cast<Type>(this);
        }
        operator const Type*()const noexcept{
            return reinterpret_cast<Type>(this);
        }

        Vector4d operator+(const Vector4d &rhs)const noexcept{
            return Vector4d(x + rhs.x,y + rhs.y,z + rhs.z,w + rhs.w);
        }
        Vector4d operator-(const Vector4d &rhs)const noexcept{
            return Vector4d(x - rhs.x,y - rhs.y,z - rhs.z,w - rhs.w);
        }
        Vector4d operator*(const Vector4d &rhs)const noexcept{
            return Vector4d(x * rhs.x,y * rhs.y,z * rhs.z,w * rhs.w);
        }
        Vector4d operator/(const Vector4d &rhs)const noexcept{
            return Vector4d(x / rhs.x,y / rhs.y,z / rhs.z,w / rhs.w);
        }

        Vector4d operator+(const Type &rhs)const noexcept{
            return Vector4d(x + rhs,y + rhs,z + rhs,w + rhs);
        }
        Vector4d operator-(const Type &rhs)const noexcept{
            return Vector4d(x - rhs,y - rhs,z - rhs,w - rhs);
        }
        Vector4d operator*(const Type &rhs)const noexcept{
            return Vector4d(x * rhs,y * rhs,z * rhs,w * rhs);
        }
        Vector4d operator/(const Type &rhs)const noexcept{
            return Vector4d(x / rhs,y / rhs,z / rhs,w / rhs);
        }


        Vector4d &operator+=(const Vector4d &rhs)noexcept{
            x += rhs.x;
            y += rhs.y;
            z += rhs.z;
            w += rhs.w;
            return *this;
        }
        Vector4d &operator-=(const Vector4d &rhs)noexcept{
            x -= rhs.x;
            y -= rhs.y;
            z -= rhs.z;
            w -= rhs.w;
            return *this;
        }
        Vector4d &operator*=(const Vector4d &rhs)noexcept{
            x *= rhs.x;
            y *= rhs.y;
            z *= rhs.z;
            w *= rhs.w;
            return *this;
        }
        Vector4d &operator/=(const Vector4d &rhs)noexcept{
            x /= rhs.x;
            y /= rhs.y;
            z /= rhs.z;
            w /= rhs.w;
            return *this;
        }

        Vector4d &operator+=(const Type &rhs)noexcept{
            x += rhs;
            y += rhs;
            z += rhs;
            w += rhs;
            return *this;
        }
        Vector4d &operator-=(const Type &rhs)noexcept{
            x -= rhs;
            y -= rhs;
            z -= rhs;
            w -= rhs;
            return *this;
        }
        Vector4d &operator*=(const Type &rhs)noexcept{
            x *= rhs;
            y *= rhs;
            z *= rhs;
            w *= rhs;
            return *this;
        }
        Vector4d &operator/=(const Type &rhs)noexcept{
            x /= rhs;
            y /= rhs;
            z /= rhs;
            w /= rhs;
            return *this;
        }

        Vector4d operator-()const noexcept{
            return Vector4d(-x,-y,-z,-w);
        }

        Type length()const noexcept{
            return std::sqrt(x * x + y * y + z * z + w * w);
        }

        Type length2()const noexcept{
            return x * x + y * y + z * z + w * w;
        }

        Vector4d &normalize()noexcept{
            *this /= length();
            return *this;
        }

        friend std::ostream &operator<<(std::ostream &os,const Vector4d<Type> &rhs){
            os<<'['<<rhs.x<<','<<rhs.y<<','<<rhs.z<<','<<rhs.w<<']';
            return os;
        }
    protected:
    private:
    };
}

#endif //_XMATH_VECTOR_H_