
#include "core/TGMatrix.h"
#include <cstring>

const TGMatrix4 TGMatrix4::Identity;

TGMatrix4::TGMatrix4(const real data[16], bool rowMajor)
{
    for(int n = 0; n < 16; n++)
    {
        myData[rowMajor ? Index(n/N,n%N) : n] = data[n];
    }
}
TGMatrix4::TGMatrix4(const TGMatrix4 &other)
{
    memcpy(myData, other.myData, sizeof(real)*16);
}

TGMatrix4 &TGMatrix4::operator =(const TGMatrix4 &other)
{
    memcpy(myData, other.myData, sizeof(real)*16);
    return *this;
}

void TGMatrix4::CreatePerspective(real fov, real ratio, real near, real far)
{
    real tangent = tan(fov/2.0);
    real top = near * tangent;
    real bottom = -top;
    real right = top * ratio;
    real left = -right;

    CreatePerspective(left, right, bottom, top, near, far);
}

void TGMatrix4::CreatePerspective(real left, real right, 
        real bottom, real top, real near, real far)
{
    TGMatrix4 &a = *this;
    a(0,0) = 2*near/(right-left);
    a(0,1) = 0;
    a(0,2) = (right + left)/(right-left);
    a(0,3) = 0;
    a(1,0) = 0;
    a(1,1) = 2*near/(top-bottom);
    a(1,2) = (top+bottom)/(top-bottom);
    a(1,3) = 0;
    a(2,0) = 0;
    a(2,1) = 0;
    a(2,2) = -(far+near)/(far-near);
    a(2,3) = -2*(far*near)/(far-near);
    a(3,0) = 0;
    a(3,1) = 0;
    a(3,2) = -1;
    a(3,3) = 0;
}

void TGMatrix4::CreateOrthogonal(real left, real right,
        real bottom, real top, real near, real far)
{
    TGMatrix4 &a = *this;
    a(0,0) = 2/(right-left);
    a(0,1) = 0;
    a(0,2) = 0;
    a(0,3) = -(right + left)/(right-left);
    a(1,0) = 0;
    a(1,1) = 2/(top-bottom);
    a(1,2) = 0;
    a(1,3) = -(top+bottom)/(top-bottom);
    a(2,0) = 0;
    a(2,1) = 0;
    a(2,2) = -2/(far-near);
    a(2,3) = -(far+near)/(far-near);
    a(3,0) = 0;
    a(3,1) = 0;
    a(3,2) = 0;
    a(3,3) = 1;
}

void TGMatrix4::CreateRotationX(real angle)
{
    TGMatrix4 &a = *this;
    a(0,0) = 1;
    a(0,1) = 0;
    a(0,2) = 0;
    a(0,3) = 0;
    a(1,0) = 0;
    a(1,1) = cos(angle);
    a(1,2) = -sin(angle);
    a(1,3) = 0;
    a(2,0) = 0;
    a(2,1) = sin(angle);
    a(2,2) = cos(angle);
    a(2,3) = 0;
    a(3,0) = 0;
    a(3,1) = 0;
    a(3,2) = 0;
    a(3,3) = 1;
}

void TGMatrix4::CreateRotationY(real angle)
{
    TGMatrix4 &a = *this;
    a(0,0) = cos(angle);
    a(0,1) = 0;
    a(0,2) = sin(angle);
    a(0,3) = 0;
    a(1,0) = 0;
    a(1,1) = 1;
    a(1,2) = 0;
    a(1,3) = 0;
    a(2,0) = -sin(angle);
    a(2,1) = 0;
    a(2,2) = cos(angle);
    a(2,3) = 0;
    a(3,0) = 0;
    a(3,1) = 0;
    a(3,2) = 0;
    a(3,3) = 1;
}

void TGMatrix4::CreateRotationZ(real angle)
{
    TGMatrix4 &a = *this;
    a(0,0) = cos(angle);
    a(0,1) = -sin(angle);
    a(0,2) = 0;
    a(0,3) = 0;
    a(1,0) = sin(angle);
    a(1,1) = cos(angle);
    a(1,2) = 0;
    a(1,3) = 0;
    a(2,0) = 0;
    a(2,1) = 0;
    a(2,2) = 1;
    a(2,3) = 0;
    a(3,0) = 0;
    a(3,1) = 0;
    a(3,2) = 0;
    a(3,3) = 1;
}

void TGMatrix4::CreateTranslation(const TGVectorF4 &pos)
{
    TGMatrix4 &a = *this;
    a(0,0) = 1;
    a(0,1) = 0;
    a(0,2) = 0;
    a(0,3) = pos.X;
    a(1,0) = 0;
    a(1,1) = 1;
    a(1,2) = 0;
    a(1,3) = pos.Y;
    a(2,0) = 0;
    a(2,1) = 0;
    a(2,2) = 1;
    a(2,3) = pos.Z;
    a(3,0) = 0;
    a(3,1) = 0;
    a(3,2) = 0;
    a(3,3) = 1;
}

void TGMatrix4::SetTranslation(const TGVectorF4 &pos)
{
    TGMatrix4 &a = *this;
    a(0,3) = pos.X;
    a(1,3) = pos.Y;
    a(2,3) = pos.Z;
}

void TGMatrix4::GetTranslation(TGVectorF4 &pos) const 
{
    const TGMatrix4 &a = *this;
    pos.X = a(0,3);
    pos.Y = a(1,3);
    pos.Z = a(2,3);
}

TGMatrix4 TGMatrix4::operator * (const TGMatrix4 &b) const
{
    TGMatrix4 c;
    const TGMatrix4 &a = *this;
    for(uint i = 0; i < 4; i++)
    {
        for(uint j = 0; j < 4; j++)
        {
            c(i,j) = 0;
            for(uint r = 0; r < 4; r++)
            {
                c(i,j) += a(i,r) * b(r,j);
            }
        }
    }
    return c;
}

TGVectorF4 TGMatrix4::operator *(const TGVectorF4 &b) const
{
    const TGMatrix4 &a = *this;
    TGVectorF4 c;
    c.X = a(0,0) * b.X + a(0,1) * b.Y + a(0,2) * b.Z + a(0,3) * b.W;
    c.Y = a(1,0) * b.X + a(1,1) * b.Y + a(1,2) * b.Z + a(1,3) * b.W;
    c.Z = a(2,0) * b.X + a(2,1) * b.Y + a(2,2) * b.Z + a(2,3) * b.W;
    c.W = a(3,0) * b.X + a(3,1) * b.Y + a(3,2) * b.Z + a(3,3) * b.W;
    return c;
}

real TGMatrix4::Determinant()
{
   TGMatrix4 &m = *this;
   real value =
   m(0,3)*m(1,2)*m(2,1)*m(3,0) - m(0,2)*m(1,3)*m(2,1)*m(3,0) - m(0,3)*m(1,1)*m(2,2)*m(3,0) + m(0,1)*m(1,3)*m(2,2)*m(3,0)+
   m(0,2)*m(1,1)*m(2,3)*m(3,0) - m(0,1)*m(1,2)*m(2,3)*m(3,0) - m(0,3)*m(1,2)*m(2,0)*m(3,1) + m(0,2)*m(1,3)*m(2,0)*m(3,1)+
   m(0,3)*m(1,0)*m(2,2)*m(3,1) - m(0,0)*m(1,3)*m(2,2)*m(3,1) - m(0,2)*m(1,0)*m(2,3)*m(3,1) + m(0,0)*m(1,2)*m(2,3)*m(3,1)+
   m(0,3)*m(1,1)*m(2,0)*m(3,2) - m(0,1)*m(1,3)*m(2,0)*m(3,2) - m(0,3)*m(1,0)*m(2,1)*m(3,2) + m(0,0)*m(1,3)*m(2,1)*m(3,2)+
   m(0,1)*m(1,0)*m(2,3)*m(3,2) - m(0,0)*m(1,1)*m(2,3)*m(3,2) - m(0,2)*m(1,1)*m(2,0)*m(3,3) + m(0,1)*m(1,2)*m(2,0)*m(3,3)+
   m(0,2)*m(1,0)*m(2,1)*m(3,3) - m(0,0)*m(1,2)*m(2,1)*m(3,3) - m(0,1)*m(1,0)*m(2,2)*m(3,3) + m(0,0)*m(1,1)*m(2,2)*m(3,3);
   return value;
}

bool TGMatrix4::Invert()
{
    TGMatrix4 m(*this);
    TGMatrix4 &t = *this;
    real det = m.Determinant();
    if(fabsf(det) < 0.001)
    {
        Debug("Determinant is %g", det);
        return false;
    }
    real factor = 1/det;
    t(0,0) = (m(1,2)*m(2,3)*m(3,1) - m(1,3)*m(2,2)*m(3,1) + m(1,3)*m(2,1)*m(3,2) - m(1,1)*m(2,3)*m(3,2) - m(1,2)*m(2,1)*m(3,3) + m(1,1)*m(2,2)*m(3,3))*factor;
    t(0,1) = (m(0,3)*m(2,2)*m(3,1) - m(0,2)*m(2,3)*m(3,1) - m(0,3)*m(2,1)*m(3,2) + m(0,1)*m(2,3)*m(3,2) + m(0,2)*m(2,1)*m(3,3) - m(0,1)*m(2,2)*m(3,3))*factor;
    t(0,2) = (m(0,2)*m(1,3)*m(3,1) - m(0,3)*m(1,2)*m(3,1) + m(0,3)*m(1,1)*m(3,2) - m(0,1)*m(1,3)*m(3,2) - m(0,2)*m(1,1)*m(3,3) + m(0,1)*m(1,2)*m(3,3))*factor;
    t(0,3) = (m(0,3)*m(1,2)*m(2,1) - m(0,2)*m(1,3)*m(2,1) - m(0,3)*m(1,1)*m(2,2) + m(0,1)*m(1,3)*m(2,2) + m(0,2)*m(1,1)*m(2,3) - m(0,1)*m(1,2)*m(2,3))*factor;
    t(1,0) = (m(1,3)*m(2,2)*m(3,0) - m(1,2)*m(2,3)*m(3,0) - m(1,3)*m(2,0)*m(3,2) + m(1,0)*m(2,3)*m(3,2) + m(1,2)*m(2,0)*m(3,3) - m(1,0)*m(2,2)*m(3,3))*factor;
    t(1,1) = (m(0,2)*m(2,3)*m(3,0) - m(0,3)*m(2,2)*m(3,0) + m(0,3)*m(2,0)*m(3,2) - m(0,0)*m(2,3)*m(3,2) - m(0,2)*m(2,0)*m(3,3) + m(0,0)*m(2,2)*m(3,3))*factor;
    t(1,2) = (m(0,3)*m(1,2)*m(3,0) - m(0,2)*m(1,3)*m(3,0) - m(0,3)*m(1,0)*m(3,2) + m(0,0)*m(1,3)*m(3,2) + m(0,2)*m(1,0)*m(3,3) - m(0,0)*m(1,2)*m(3,3))*factor;
    t(1,3) = (m(0,2)*m(1,3)*m(2,0) - m(0,3)*m(1,2)*m(2,0) + m(0,3)*m(1,0)*m(2,2) - m(0,0)*m(1,3)*m(2,2) - m(0,2)*m(1,0)*m(2,3) + m(0,0)*m(1,2)*m(2,3))*factor;
    t(2,0) = (m(1,1)*m(2,3)*m(3,0) - m(1,3)*m(2,1)*m(3,0) + m(1,3)*m(2,0)*m(3,1) - m(1,0)*m(2,3)*m(3,1) - m(1,1)*m(2,0)*m(3,3) + m(1,0)*m(2,1)*m(3,3))*factor;
    t(2,1) = (m(0,3)*m(2,1)*m(3,0) - m(0,1)*m(2,3)*m(3,0) - m(0,3)*m(2,0)*m(3,1) + m(0,0)*m(2,3)*m(3,1) + m(0,1)*m(2,0)*m(3,3) - m(0,0)*m(2,1)*m(3,3))*factor;
    t(2,2) = (m(0,1)*m(1,3)*m(3,0) - m(0,3)*m(1,1)*m(3,0) + m(0,3)*m(1,0)*m(3,1) - m(0,0)*m(1,3)*m(3,1) - m(0,1)*m(1,0)*m(3,3) + m(0,0)*m(1,1)*m(3,3))*factor;
    t(2,3) = (m(0,3)*m(1,1)*m(2,0) - m(0,1)*m(1,3)*m(2,0) - m(0,3)*m(1,0)*m(2,1) + m(0,0)*m(1,3)*m(2,1) + m(0,1)*m(1,0)*m(2,3) - m(0,0)*m(1,1)*m(2,3))*factor;
    t(3,0) = (m(1,2)*m(2,1)*m(3,0) - m(1,1)*m(2,2)*m(3,0) - m(1,2)*m(2,0)*m(3,1) + m(1,0)*m(2,2)*m(3,1) + m(1,1)*m(2,0)*m(3,2) - m(1,0)*m(2,1)*m(3,2))*factor;
    t(3,1) = (m(0,1)*m(2,2)*m(3,0) - m(0,2)*m(2,1)*m(3,0) + m(0,2)*m(2,0)*m(3,1) - m(0,0)*m(2,2)*m(3,1) - m(0,1)*m(2,0)*m(3,2) + m(0,0)*m(2,1)*m(3,2))*factor;
    t(3,2) = (m(0,2)*m(1,1)*m(3,0) - m(0,1)*m(1,2)*m(3,0) - m(0,2)*m(1,0)*m(3,1) + m(0,0)*m(1,2)*m(3,1) + m(0,1)*m(1,0)*m(3,2) - m(0,0)*m(1,1)*m(3,2))*factor;
    t(3,3) = (m(0,1)*m(1,2)*m(2,0) - m(0,2)*m(1,1)*m(2,0) + m(0,2)*m(1,0)*m(2,1) - m(0,0)*m(1,2)*m(2,1) - m(0,1)*m(1,0)*m(2,2) + m(0,0)*m(1,1)*m(2,2))*factor;
    return true;
}

bool TGMatrix4::InvertTranspose()
{
    TGMatrix4 m(*this);
    TGMatrix4 &t = *this;
    real det = m.Determinant();
    if(fabsf(det) < 0.001)
    {
        Debug("Determinant is %g", det);
        return false;
    }
    real factor = 1/det;
    t(0,0) = (m(1,2)*m(2,3)*m(3,1) - m(1,3)*m(2,2)*m(3,1) + m(1,3)*m(2,1)*m(3,2) - m(1,1)*m(2,3)*m(3,2) - m(1,2)*m(2,1)*m(3,3) + m(1,1)*m(2,2)*m(3,3))*factor;
    t(1,0) = (m(0,3)*m(2,2)*m(3,1) - m(0,2)*m(2,3)*m(3,1) - m(0,3)*m(2,1)*m(3,2) + m(0,1)*m(2,3)*m(3,2) + m(0,2)*m(2,1)*m(3,3) - m(0,1)*m(2,2)*m(3,3))*factor;
    t(2,0) = (m(0,2)*m(1,3)*m(3,1) - m(0,3)*m(1,2)*m(3,1) + m(0,3)*m(1,1)*m(3,2) - m(0,1)*m(1,3)*m(3,2) - m(0,2)*m(1,1)*m(3,3) + m(0,1)*m(1,2)*m(3,3))*factor;
    t(3,0) = (m(0,3)*m(1,2)*m(2,1) - m(0,2)*m(1,3)*m(2,1) - m(0,3)*m(1,1)*m(2,2) + m(0,1)*m(1,3)*m(2,2) + m(0,2)*m(1,1)*m(2,3) - m(0,1)*m(1,2)*m(2,3))*factor;
    t(0,1) = (m(1,3)*m(2,2)*m(3,0) - m(1,2)*m(2,3)*m(3,0) - m(1,3)*m(2,0)*m(3,2) + m(1,0)*m(2,3)*m(3,2) + m(1,2)*m(2,0)*m(3,3) - m(1,0)*m(2,2)*m(3,3))*factor;
    t(1,1) = (m(0,2)*m(2,3)*m(3,0) - m(0,3)*m(2,2)*m(3,0) + m(0,3)*m(2,0)*m(3,2) - m(0,0)*m(2,3)*m(3,2) - m(0,2)*m(2,0)*m(3,3) + m(0,0)*m(2,2)*m(3,3))*factor;
    t(2,1) = (m(0,3)*m(1,2)*m(3,0) - m(0,2)*m(1,3)*m(3,0) - m(0,3)*m(1,0)*m(3,2) + m(0,0)*m(1,3)*m(3,2) + m(0,2)*m(1,0)*m(3,3) - m(0,0)*m(1,2)*m(3,3))*factor;
    t(3,1) = (m(0,2)*m(1,3)*m(2,0) - m(0,3)*m(1,2)*m(2,0) + m(0,3)*m(1,0)*m(2,2) - m(0,0)*m(1,3)*m(2,2) - m(0,2)*m(1,0)*m(2,3) + m(0,0)*m(1,2)*m(2,3))*factor;
    t(0,2) = (m(1,1)*m(2,3)*m(3,0) - m(1,3)*m(2,1)*m(3,0) + m(1,3)*m(2,0)*m(3,1) - m(1,0)*m(2,3)*m(3,1) - m(1,1)*m(2,0)*m(3,3) + m(1,0)*m(2,1)*m(3,3))*factor;
    t(1,2) = (m(0,3)*m(2,1)*m(3,0) - m(0,1)*m(2,3)*m(3,0) - m(0,3)*m(2,0)*m(3,1) + m(0,0)*m(2,3)*m(3,1) + m(0,1)*m(2,0)*m(3,3) - m(0,0)*m(2,1)*m(3,3))*factor;
    t(2,2) = (m(0,1)*m(1,3)*m(3,0) - m(0,3)*m(1,1)*m(3,0) + m(0,3)*m(1,0)*m(3,1) - m(0,0)*m(1,3)*m(3,1) - m(0,1)*m(1,0)*m(3,3) + m(0,0)*m(1,1)*m(3,3))*factor;
    t(3,2) = (m(0,3)*m(1,1)*m(2,0) - m(0,1)*m(1,3)*m(2,0) - m(0,3)*m(1,0)*m(2,1) + m(0,0)*m(1,3)*m(2,1) + m(0,1)*m(1,0)*m(2,3) - m(0,0)*m(1,1)*m(2,3))*factor;
    t(0,3) = (m(1,2)*m(2,1)*m(3,0) - m(1,1)*m(2,2)*m(3,0) - m(1,2)*m(2,0)*m(3,1) + m(1,0)*m(2,2)*m(3,1) + m(1,1)*m(2,0)*m(3,2) - m(1,0)*m(2,1)*m(3,2))*factor;
    t(1,3) = (m(0,1)*m(2,2)*m(3,0) - m(0,2)*m(2,1)*m(3,0) + m(0,2)*m(2,0)*m(3,1) - m(0,0)*m(2,2)*m(3,1) - m(0,1)*m(2,0)*m(3,2) + m(0,0)*m(2,1)*m(3,2))*factor;
    t(2,3) = (m(0,2)*m(1,1)*m(3,0) - m(0,1)*m(1,2)*m(3,0) - m(0,2)*m(1,0)*m(3,1) + m(0,0)*m(1,2)*m(3,1) + m(0,1)*m(1,0)*m(3,2) - m(0,0)*m(1,1)*m(3,2))*factor;
    t(3,3) = (m(0,1)*m(1,2)*m(2,0) - m(0,2)*m(1,1)*m(2,0) + m(0,2)*m(1,0)*m(2,1) - m(0,0)*m(1,2)*m(2,1) - m(0,1)*m(1,0)*m(2,2) + m(0,0)*m(1,1)*m(2,2))*factor;
    return true;
}
//TGMatrix4::operator const char *() const
//{
//    ostringstream out;
//    out<<"[ ";
//    for(int i = 0; i < 4; i++)
//    {
//        for(int j = 0; j < 4; j++)
//        {
//            out<<(*this)(i,j)<<" ";
//        }
//        out<<"; ";
//    }
//    out<<" ]";
//    return out.str();
//}
