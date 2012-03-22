
#ifndef TGSOLVER_H_
#define TGSOLVER_H_

#include "core/TGDef.h"
#include "model/TGMeshSystem.h"

class TGSolver
{
    public:
    const real dx;
    const real dy;
    const real dx2;
    const real dy2;
    const real c2;
    const real invdxdy;

    TGSolver(real dx, real dy, real c)
        : dx(dx),dy(dy), dx2(dx*dx), dy2(dy*dy), c2(c*c), invdxdy(1./(dx*dy)) { }

    virtual void Advance(TGMeshSystem &system, real dt) = 0;
};

class TGExplicitSolver : public TGSolver
{
    const real mufactor;
    public:
    TGExplicitSolver(real dx, real dy, real c, real mu)
        : TGSolver(dx,dy,c), mufactor(4*mu/3.) 
    {
        Debug("At init: dx: %g, dy: %g", this->dx,this->dy);
    }

    virtual void Advance(TGMeshSystem &system, real dt);
};

#endif
