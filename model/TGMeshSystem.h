
#ifndef TGMESHSYSTEM_H_
#define TGMESHSYSTEM_H_

#include "visual/TGMesh.h"
#include <cstring>

class TGMeshSystem
{
    uint myHeight;
    uint myWidth;
    uint myCount;
    uint myCurrent;
    real *myData;

    uint twrap(int t)
    {
        if (t < 0)
            t += myCount;
        if (t >= (int)myCount)
            t -= myCount;

        return t;
    }

    uint index(uint k, uint i, uint j)
    {
        return twrap(k) * myWidth*myHeight + i * myWidth + j;
    }

    public:
    TGMeshSystem(uint width, uint height, uint count)
        : myHeight(height), myWidth(width), myCount(count), myCurrent(0), myData(new real[height*width*count])
    {
        memset(myData, 0, sizeof(GLfloat)*height*width*count);
    }
    // k=+1: next step
    real &operator () (int k, uint i, uint j)
    {
        return myData[index(myCurrent+k-1,i,j)];
    }

    uint GetHeight()
    {
        return myHeight;
    }
    uint GetWidth()
    {
        return myWidth;
    }

    real *Commit()
    {
        real *data = myData + index(myCurrent, 0,0);
        myCurrent = twrap(myCurrent + 1);
        return data;
    }
    
};

#endif
