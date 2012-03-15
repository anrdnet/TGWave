
#ifndef TGVECTOR_H_
#define TGVECTOR_H_

#include <string>
#include "core/TGDef.h"
#include <sstream>
#include <cmath>

using namespace std;

template<typename T>
class TGVectorT4
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

    TGVectorT4()
        : X(0), Y(0), Z(0), W(1)
    {

    }

    TGVectorT4(T x, T y, T z)
        : X(x), Y(y), Z(z), W(1)
    {
    }

    TGVectorT4(T x, T y, T z, T w)
        : X(x), Y(y), Z(z), W(w)
    {
    }
    
    void Floor();

    TGVectorT4 ComponentMul(const TGVectorT4 &b) const
    {
        return TGVectorT4(X*b.X, Y*b.Y, Z*b.Z);
    }

    TGVectorT4 operator+ (const TGVectorT4 &b) const
    {
        return TGVectorT4(X + b.X, Y + b.Y, Z + b.Z);
    }

    TGVectorT4 operator- (const TGVectorT4 &b) const
    {
        return TGVectorT4(X - b.X, Y - b.Y, Z - b.Z);
    }

    void operator+= (const TGVectorT4 &b) 
    {
        X += b.X;
        Y += b.Y;
        Z += b.Z;
    }

    void operator-= (const TGVectorT4 &b)
    {
        X -= b.X;
        Y -= b.Y;
        Z -= b.Z;
    }

    T operator* (const TGVectorT4 &b) const
    {
        return X * b.X + Y * b.Y + Z * b.Z;
    }

    TGVectorT4 operator% (const TGVectorT4 &b) const
    {
        return TGVectorT4(Y*b.Z-Z*b.Y, Z*b.X-X*b.Z, X*b.Y-Y*b.X);
    }

    TGVectorT4 operator* (T s) const
    {
        return TGVectorT4(X*s,Y*s,Z*s);
    }

    TGVectorT4 operator/ (T s) const
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

    bool operator== (const TGVectorT4 &b) const
    {
        return X == b.X && Y == b.Y && Z == b.Z && W == b.W;
    }
    
    bool operator!= (const TGVectorT4 &b) const
    {
        return !((*this) == b);
    }

    bool operator< (const TGVectorT4 &b) const
    {
        return X < b.X && Y < b.Y && Z < b.Z;
    }
    bool operator> (const TGVectorT4 &b) const
    {
        return X > b.X && Y > b.Y && Z > b.Z;
    }
    bool operator<= (const TGVectorT4 &b) const
    {
        return X <= b.X && Y <= b.Y && Z <= b.Z && W <= b.W;
    }
    bool operator>= (const TGVectorT4 &b) const
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
TGVectorT4<T>::operator const string () const
{
    ostringstream out;
    out<<"( ";
    for(int i = 0; i < 3; i++)
        out<<Elements[i]<<", ";
    out<<Elements[3]<<" )";
    return out.str();
}

template<typename T>
void TGVectorT4<T>::Floor()
{
    X = floor(X);
    Y = floor(Y);
    Z = floor(Z);
}

typedef TGVectorT4<real> TGVectorF4;
typedef TGVectorT4<int> TGVectorI4;

extern const TGVectorF4 ZeroF;
extern const TGVectorF4 UnitXF;
extern const TGVectorF4 UnitYF;
extern const TGVectorF4 UnitZF;
extern const TGVectorF4 OneF;
extern const TGVectorF4 UnitF[3];
extern const TGVectorI4 ZeroI;
extern const TGVectorI4 UnitXI;
extern const TGVectorI4 UnitYI;
extern const TGVectorI4 UnitZI;
extern const TGVectorI4 OneI;
extern const TGVectorI4 UnitI[3];


#endif
