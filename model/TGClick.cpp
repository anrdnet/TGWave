
#include "TGClick.h"
#include <cmath>
#define PI 3.14159265358979323846

real TGClick::Val(real x, real y, real centerX, real centerY)
{
    return myParams.Scale * myParams.NewHeight*exp(-myParams.Shape/myParams.Scale*((x-centerX)*(x-centerX) + (y-centerY)*(y-centerY)));
}

const uint k = 0;

void TGClick::Click(real x, real y)
{
    uint h = myMesh.GetHeight();
    uint w = myMesh.GetWidth();
    real avg = 0;
    for(uint i = 0; i < h; i++)
    {
        for(uint j = 0; j < w; j++)
        {
            myMesh(k, i, j) += Val(j*myDx, i*myDy, x, y);
            myMesh(k-1, i, j) += Val(j*myDx, i*myDy, x, y);
            avg += myMesh(k, i, j);
        }
    }
    avg /= h*w;
    myMesh.Drift() = avg;
}
