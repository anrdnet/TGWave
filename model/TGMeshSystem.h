
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

    uint index(int k, int i, int j)
    {
        if(i < 0)
            i += myHeight;
        if(j < 0)
            j += myWidth;
        if(i >= myHeight)
            i -= myHeight;
        if(j >= myWidth)
            j -= myWidth;
        uint ki = twrap(k);
        return ki * myWidth*myHeight + i * myWidth + j;
    }

    public:
    TGMeshSystem(uint width, uint height, uint count)
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
