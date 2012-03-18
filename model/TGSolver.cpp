
#include "TGSolver.h"

//Just to improve readabillity
const uint k = 0;

void TGExplicitSolver::Advance(TGMeshSystem &phi, real dt)
{
    uint h = phi.GetHeight();
    uint w = phi.GetWidth();
    for (uint i = 0; i < h; i++)
    {
        for(uint j = 0; j < w; j++)
        {
            phi(k+1,i,j) = 0;
            if(i != h-1)
            {
                phi(k+1, i, j) += (phi(k,i+1,j) - phi(k,i,j))/dy*dx;
                phi(k+1, i, j) += 4*mu/3*((phi(k,i+1,j) - phi(k-1,i+1,j))/dt - (phi(k,i,j) - phi(k-1,i,j))/dt)/dy*dx;
            }
            if(j != w-1)
            {
                phi(k+1, i, j) += (phi(k,i,j+1) - phi(k,i,j))/dx*dy;
                phi(k+1, i, j) += 4*mu/3*((phi(k,i,j+1) - phi(k-1,i,j+1))/dt - (phi(k,i,j) - phi(k-1,i,j))/dt)/dy*dx;
            }
            if(i != 0)
            {
                phi(k+1, i, j) += (phi(k,i-1,j) - phi(k,i,j))/dy*dx;
                phi(k+1, i, j) += 4*mu/3*((phi(k,i-1,j) - phi(k-1,i-1,j))/dt - (phi(k,i,j) - phi(k-1,i,j))/dt)/dy*dx;
            }
            if(j != 0)
            {
                phi(k+1, i, j) += (phi(k,i,j-1) - phi(k,i,j))/dx*dy;
                phi(k+1, i, j) += 4*mu/3*((phi(k,i,j-1) - phi(k-1,i,j-1))/dt - (phi(k,i,j) - phi(k-1,i,j))/dt)/dy*dx;
            }

            phi(k+1,i,j) *= dt*dt*c2;
            phi(k+1,i,j) += 2*phi(k,i,j)-phi(k-1, i, j);
        }
    }
}
