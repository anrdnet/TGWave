
#ifndef TGSOLVER_H_
#define TGSOLVER_H_

#include "core/TGDef.h"
#include "model/TGMeshSystem.h"

class TGSolver
{
    public:
    const real dx;
    const real dy;
    const real c2;

    TGSolver(real dx, real dy, real c)
        :dx(dx),dy(dy), c2(c*c) { }

    virtual void Advance(TGMeshSystem &system, real dt) = 0;
};

class TGExplicitSolver : public TGSolver
{
    real mu;
    public:
    TGExplicitSolver(real dx, real dy, real c, real mu)
        : TGSolver(dx,dy,c), mu(mu) { }

    virtual void Advance(TGMeshSystem &system, real dt);
};

#endif
