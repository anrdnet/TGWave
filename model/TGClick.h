
#ifndef TGCLICK_H_
#define TGCLICK_H_

#include "model/TGMeshSystem.h"
#include "TGInterface.h"

class TGClick
{
    real myDx;
    real myDy;
    SimParams &myParams;
    TGMeshSystem &myMesh;

    real Val(real x, real y, real centerX, real centerY);

    public:
    TGClick(TGMeshSystem &mesh, real dx, real dy, SimParams &params)
        :myDx(dx), myDy(dy), myParams(params), myMesh(mesh)
    {
    }
    
    void Click(real x, real y);
};

#endif
