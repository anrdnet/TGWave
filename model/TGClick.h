
#ifndef TGCLICK_H_
#define TGCLICK_H_

#include "model/TGMeshSystem.h"

class TGClick
{
    real myShape;
    real myHeight;
    real myDx;
    real myDy;
    TGMeshSystem &myMesh;

    real Val(real x, real y, real centerX, real centerY);

    public:
    TGClick(TGMeshSystem &mesh, real dx, real dy)
        :myDx(dx), myDy(dy), myMesh(mesh)
    {
        myShape = 200;
        myHeight = 1;
    }
    
    void SetParams(real shape, real height)
    {
        myShape = shape;
        myHeight = height;
    }

    void Click(real x, real y);
};

#endif
