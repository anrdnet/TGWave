
#ifndef TGMESHSYSTEM_H_
#define TGMESHSYSTEM_H_

#include "visual/TGMesh.h"
#include <cstring>

class TGMeshSystem
{
    const uint myHeight;
    const uint myWidth;
    const uint myCount;
    real myDrift;
    uint myCurrent;
    real *myData;
    TGVectorF4 *myNormals;

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
        //Bug(i < 0 || i >= (int)myHeight || j < 0 || j >= (int)myWidth, "Invalid mesh system index");
        uint ki = twrap(k);
        return ki * myWidth*myHeight + i * myWidth + j;
    }

    public:
    TGMeshSystem(uint height, uint width, uint count)
        : myHeight(height), myWidth(width), myCount(count), myCurrent(0), 
        myData(new real[height*width*count]), 
        myNormals(new TGVectorF4[height*width*count])
    {
        memset(myData, 0, sizeof(GLfloat)*height*width*count);
        memset(myNormals, 0, sizeof(TGVectorF4)*height*width*count);
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

    TGVectorF4 &Normal(int k, int i, int j)
    {
        return myNormals[index(myCurrent+k-1,i,j)];
    }

    real &Drift()
    {
        return myDrift;
    }

    uint GetHeight()
    {
        return myHeight;
    }
    uint GetWidth()
    {
        return myWidth;
    }

    TGVectorF4 *Normals()
    {
        return myNormals + index(myCurrent, 0,0);
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
    void Reset()
    {
        for(uint k = 0; k < myCount; k++)
        {
            for(uint i = 0; i < myHeight; i++)
            {
                for(uint j = 0; j < myWidth; j++)
                {
                    (*this)(k,i,j) = 0;
                }
            }
        }
    }   
};

#endif
