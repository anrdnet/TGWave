
#ifndef ANMATRIX_H_
#define ANMATRIX_H_

#include <cmath>
#include "core/ANDef.h"
#include "core/ANError.h"
#include "core/ANVector.h"

class ANMatrix4
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
    static const ANMatrix4 Identity;

    ANMatrix4()
        : myData ({
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        })
    {

    }

    ANMatrix4(const real data[N*N], bool rowMajor = true);


    real& operator() (const int i, const int j)
    {
        if(i >= N || j >= N)
            throw ANError(ANErrorCode::MatOutOfBounds);
        return myData[Index(i, j)];
    }

    real operator() (const int i, const int j) const
    {
        if(i >= N || j >= N)
            throw ANError(ANErrorCode::MatOutOfBounds);
        return myData[Index(i, j)];
    }

    void SetTranslation(const ANVectorF4 &pos);
    void GetTranslation(ANVectorF4 &pos) const;

    void CreatePerspective(real fov, real ratio, real near, real far);
    void CreatePerspective(real left, real right, 
            real bottom, real top, real near, real far);
    void CreateOrthogonal(real left, real right,
            real bottom, real top, real near, real far);
    void CreateRotationX(real angle);
    void CreateRotationY(real angle);
    void CreateRotationZ(real angle);
    void CreateTranslation(const ANVectorF4 &pos);

    ANMatrix4 operator * (const ANMatrix4 b) const;
    operator const real*() const
    {
        return myData;
    }

    operator const string() const;
};

#endif
