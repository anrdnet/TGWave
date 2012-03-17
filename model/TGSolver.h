
#ifndef TGSOLVER_H_
#define TGSOLVER_H_

#include "core/TGDef.h"
#include "model/TGMeshSystem.h"

class TGSolver
{
    public:
    const uint dx;
    const uint dy;
    const real c2;

    TGSolver(uint dx, uint dy, real c)
        :dx(dx),dy(dy), c2(c*c) { }

    virtual void Advance(TGMeshSystem &system, real dt) = 0;
};

class TGExplicitSolver : public TGSolver
{
    public:
    TGExplicitSolver(uint dx, uint dy, real c)
        : TGSolver(dx,dy,c) { }
    virtual void Advance(TGMeshSystem &system, real dt);
};

#endif
