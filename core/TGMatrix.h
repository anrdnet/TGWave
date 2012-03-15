
#ifndef TGMATRIX_H_
#define TGMATRIX_H_

#include <cmath>
#include "core/TGDef.h"
#include "core/TGError.h"
#include "core/TGVector.h"

class TGMatrix4
{
    static const int N = 4;
    real myData[N*N];
    int Index(int i, int j) const
    {
        return j*N+i;
    }
    void Coord(int index, int &i, int &j) const
    {
        i = index % N;
        j = index / N;
    }
    public:
    static const TGMatrix4 Identity;

    TGMatrix4()
        : myData ({
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        })
    {

    }

    TGMatrix4(const real data[N*N], bool rowMajor = true);


    real& operator() (const int i, const int j)
    {
        if(i >= N || j >= N)
            throw TGError(TGErrorCode::MatOutOfBounds);
        return myData[Index(i, j)];
    }

    real operator() (const int i, const int j) const
    {
        if(i >= N || j >= N)
            throw TGError(TGErrorCode::MatOutOfBounds);
        return myData[Index(i, j)];
    }

    void SetTranslation(const TGVectorF4 &pos);
    void GetTranslation(TGVectorF4 &pos) const;

    void CreatePerspective(real fov, real ratio, real near, real far);
    void CreatePerspective(real left, real right, 
            real bottom, real top, real near, real far);
    void CreateOrthogonal(real left, real right,
            real bottom, real top, real near, real far);
    void CreateRotationX(real angle);
    void CreateRotationY(real angle);
    void CreateRotationZ(real angle);
    void CreateTranslation(const TGVectorF4 &pos);

    TGMatrix4 operator * (const TGMatrix4 b) const;
    operator const real*() const
    {
        return myData;
    }

    operator const string() const;
};

#endif
