
#include "TGSolver.h"

//Just to improve readabillity
const uint k = 0;

void TGExplicitSolver::Advance(TGMeshSystem &phi, real dt)
{
    for (uint i = 0; i < phi.GetHeight(); i++)
    {
        for(uint j = 0; j < phi.GetWidth(); i++)
        {
            phi(k+1,i,j) = 2*phi(k,i,j) - phi(k-1,i,j) + dt*dt*(1);
        }
    }
}
