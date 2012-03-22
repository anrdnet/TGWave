
#ifndef TGMESHSYSTEM_H_
#define TGMESHSYSTEM_H_

#include "visual/TGMesh.h"
#include <cstring>

class TGMeshSystem
{
    const uint myHeight;
    const uint myWidth;
    const uint myCount;
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

    uint index(int k, int i, int j)
    {
        Bug(i < 0 || i >= (int)myHeight || j < 0 || j >= (int)myWidth, "Invalid mesh system index");
        uint ki = twrap(k);
        return ki * myWidth*myHeight + i * myWidth + j;
    }

    public:
    TGMeshSystem(uint height, uint width, uint count)
        : myHeight(height), myWidth(width), myCount(count), myCurrent(0), myData(new real[height*width*count])
    {
        memset(myData, 0, sizeof(GLfloat)*height*width*count);
    }

    ~TGMeshSystem()
    {
        delete [] myData;
        myData = NULL;
    }
    // k=+1: next step
    real &operator () (int k, int i, int j)
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

    void SetData(real *data)
    {
        memcpy(myData + index(myCurrent, 0, 0), data, myHeight*myWidth*sizeof(real));
    }
    
};

#endif
