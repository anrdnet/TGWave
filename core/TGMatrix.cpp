
#include <sstream>
#include "core/ANMatrix.h"

const ANMatrix4 ANMatrix4::Identity;

ANMatrix4::ANMatrix4(const real data[16], bool rowMajor)
{
    for(int n = 0; n < 16; n++)
    {
        myData[rowMajor ? Index(n/N,n%N) : n] = data[n];
    }
}

void ANMatrix4::CreatePerspective(real fov, real ratio, real near, real far)
{
    real tangent = tan(fov/2.0);
    real top = near * tangent;
    real bottom = -top;
    real right = top * ratio;
    real left = -right;

    CreatePerspective(left, right, bottom, top, near, far);
}

void ANMatrix4::CreatePerspective(real left, real right, 
        real bottom, real top, real near, real far)
{
    ANMatrix4 &a = *this;
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

void ANMatrix4::CreateOrthogonal(real left, real right,
        real bottom, real top, real near, real far)
{
    ANMatrix4 &a = *this;
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

void ANMatrix4::CreateRotationX(real angle)
{
    ANMatrix4 &a = *this;
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

void ANMatrix4::CreateRotationY(real angle)
{
    ANMatrix4 &a = *this;
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

void ANMatrix4::CreateRotationZ(real angle)
{
    ANMatrix4 &a = *this;
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

void ANMatrix4::CreateTranslation(const ANVectorF4 &pos)
{
    ANMatrix4 &a = *this;
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

void ANMatrix4::SetTranslation(const ANVectorF4 &pos)
{
    ANMatrix4 &a = *this;
    a(0,3) = pos.X;
    a(1,3) = pos.Y;
    a(2,3) = pos.Z;
}

void ANMatrix4::GetTranslation(ANVectorF4 &pos) const 
{
    const ANMatrix4 &a = *this;
    pos.X = a(0,3);
    pos.Y = a(1,3);
    pos.Z = a(2,3);
}

ANMatrix4 ANMatrix4::operator * (const ANMatrix4 b) const
{
    ANMatrix4 c;
    const ANMatrix4 &a = *this;
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

ANMatrix4::operator const string () const
{
    ostringstream out;
    out<<"[ ";
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            out<<(*this)(i,j)<<" ";
        }
        out<<"; ";
    }
    out<<" ]";
    return out.str();
}
