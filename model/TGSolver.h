
#ifndef TGSOLVER_H_
#define TGSOLVER_H_

#include "core/TGDef.h"
#include "model/TGMeshSystem.h"
#include "TGInterface.h"
class TGSolver
{
    public:
    const real dx;
    const real dy;
    const real dx2;
    const real dy2;
    const SimParams &myParams;

    TGSolver(real dx, real dy, const SimParams &params)
        : dx(dx),dy(dy), dx2(dx*dx), dy2(dy*dy), myParams(params) { }

    virtual void Advance(TGMeshSystem &system, real dt) = 0;
};

class TGExplicitSolver : public TGSolver
{
    public:
    TGExplicitSolver(real dx, real dy, SimParams &params)
        : TGSolver(dx,dy,params)
    {
        //Debug("At init: dx: %g, dy: %g", this->dx,this->dy);
    }

    virtual void Advance(TGMeshSystem &system, real dt);
};

#endif
