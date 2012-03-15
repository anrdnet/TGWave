
#ifndef ANVECTOR_H_
#define ANVECTOR_H_

#include <string>
#include "core/ANDef.h"
#include <sstream>
#include <cmath>

using namespace std;

template<typename T>
class ANVectorT4
{
    public:
    union
    {
        struct
        {
            T X;
            T Y;
            T Z;
            T W;
        };
        T Elements[4];
    };

    ANVectorT4()
        : X(0), Y(0), Z(0), W(1)
    {

    }

    ANVectorT4(T x, T y, T z)
        : X(x), Y(y), Z(z), W(1)
    {
    }

    ANVectorT4(T x, T y, T z, T w)
        : X(x), Y(y), Z(z), W(w)
    {
    }
    
    void Floor();

    ANVectorT4 ComponentMul(const ANVectorT4 &b) const
    {
        return ANVectorT4(X*b.X, Y*b.Y, Z*b.Z);
    }

    ANVectorT4 operator+ (const ANVectorT4 &b) const
    {
        return ANVectorT4(X + b.X, Y + b.Y, Z + b.Z);
    }

    ANVectorT4 operator- (const ANVectorT4 &b) const
    {
        return ANVectorT4(X - b.X, Y - b.Y, Z - b.Z);
    }

    void operator+= (const ANVectorT4 &b) 
    {
        X += b.X;
        Y += b.Y;
        Z += b.Z;
    }

    void operator-= (const ANVectorT4 &b)
    {
        X -= b.X;
        Y -= b.Y;
        Z -= b.Z;
    }

    T operator* (const ANVectorT4 &b) const
    {
        return X * b.X + Y * b.Y + Z * b.Z;
    }

    ANVectorT4 operator* (T s) const
    {
        return ANVectorT4(X*s,Y*s,Z*s);
    }

    ANVectorT4 operator/ (T s) const
    {
        return (*this)*(1/s);
    }

    void operator*= (T s) 
    {
        X *= s;
        Y *= s;
        Z *= s;
    }

    void operator/= (T s)
    {
        X /= s;
        Y /= s;
        Z /= s;
    }

    bool operator== (const ANVectorT4 &b) const
    {
        return X == b.X && Y == b.Y && Z == b.Z && W == b.W;
    }
    
    bool operator!= (const ANVectorT4 &b) const
    {
        return !((*this) == b);
    }

    bool operator< (const ANVectorT4 &b) const
    {
        return X < b.X && Y < b.Y && Z < b.Z;
    }
    bool operator> (const ANVectorT4 &b) const
    {
        return X > b.X && Y > b.Y && Z > b.Z;
    }
    bool operator<= (const ANVectorT4 &b) const
    {
        return X <= b.X && Y <= b.Y && Z <= b.Z && W <= b.W;
    }
    bool operator>= (const ANVectorT4 &b) const
    {
        return X >= b.X && Y >= b.Y && Z >= b.Z && W >= b.W;
    }

    operator const string () const;

    real Length()
    {
        return sqrt(X*X+Y*Y+Z*Z);
    }

    void Normalize()
    {
        *this /= Length();
    }

} __attribute__((packed));

template<typename T>
ANVectorT4<T>::operator const string () const
{
    ostringstream out;
    out<<"( ";
    for(int i = 0; i < 3; i++)
        out<<Elements[i]<<", ";
    out<<Elements[3]<<" )";
    return out.str();
}

template<typename T>
void ANVectorT4<T>::Floor()
{
    X = floor(X);
    Y = floor(Y);
    Z = floor(Z);
}

typedef ANVectorT4<real> ANVectorF4;
typedef ANVectorT4<int> ANVectorI4;

extern const ANVectorF4 ZeroF;
extern const ANVectorF4 UnitXF;
extern const ANVectorF4 UnitYF;
extern const ANVectorF4 UnitZF;
extern const ANVectorF4 OneF;
extern const ANVectorF4 UnitF[3];
extern const ANVectorI4 ZeroI;
extern const ANVectorI4 UnitXI;
extern const ANVectorI4 UnitYI;
extern const ANVectorI4 UnitZI;
extern const ANVectorI4 OneI;
extern const ANVectorI4 UnitI[3];


#endif
