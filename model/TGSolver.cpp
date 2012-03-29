
#include "TGSolver.h"

//Just to improve readabillity
const uint k = 0;

void TGExplicitSolver::Advance(TGMeshSystem &phi, real dt)
{
    //Debug("dx:%g, dy:%g",dx,dy);
    const uint h = phi.GetHeight();
    const uint w = phi.GetWidth();
    const real invdt = 1./dt;
    const real c2 = myParams.c * myParams.c;
    const real mufactor = 4./3 * myParams.mu;
    const real invdxdy = 1./(dx*dy);
    const real invdx = 1./dx;
    const real invdy = 1./dy;
    for (uint i = 1; i < h-1; i++)
    {
        for(uint j = 1; j < w-1; j++)
        {
            const real phidt = (phi(k,i,j) - phi(k-1,i,j))*invdt;
            const real phik = phi(k,i,j);
            const real phic1 = phi(k,i+1,j);
            const real phic2 = phi(k,i,j+1);
            const real phic3 = phi(k,i-1,j);
            const real phic4 = phi(k,i,j-1);
            phi(k+1, i, j) = ((phic1 + phic3 - 2*phik + mufactor*((phic1 + phic3 - phi(k-1,i+1,j) - phi(k-1,i-1,j))*invdt - 2*phidt))*dx2 +
                             (phic2 + phic4 - 2*phik + mufactor*((phic2 + phic4 - phi(k-1,i,j+1) - phi(k-1, i, j-1))*invdt - 2*phidt))*dy2)
                             * dt*dt*c2*invdxdy + 2*phik - phi(k-1, i, j);
            phi.Normal(k+1,i,j) = TGVectorF4( -(phic2 - phic4)*0.5*invdx,-(phic1 - phic3)*0.5*invdy, 1, 0);
        }
    }
    // i = 0, j = 0;
    {
        const real phidt = (phi(k,0,0) - phi(k-1,0,0))*invdt;
        const real phik = phi(k,0,0);
        const real phic1 = phi(k,0+1,0);
        const real phic2 = phi(k,0,0+1);
        phi(k+1,0,0) = ((phic1 - phik + mufactor*((phic1 - phi(k-1,0+1,0))*invdt - phidt))*dx2 +
                        (phic2 - phik + mufactor*((phic2 - phi(k-1,0,0+1))*invdt - phidt))*dy2)
                        * dt*dt*c2*invdxdy + 2*phik-phi(k-1,0,0);
        phi.Normal(k+1,0,0) = TGVectorF4( -(phic2 - phik)*invdx,-(phic1 - phik)*invdy, 1, 0);
    }
    // i = 0, j = ...
    for(uint j = 1; j < w-1; j++)
    {
        const real phidt = (phi(k,0,j) - phi(k-1,0,j))*invdt;
        const real phik = phi(k,0,j);
        const real phic1 = phi(k,0+1,j);
        const real phic2 = phi(k,0,j+1);
        const real phic4 = phi(k,0,j-1);
        phi(k+1,0,j) = ((phic1 - phik + mufactor*((phic1 - phi(k-1,0+1,j))*invdt - phidt))*dx2 +
                       (phic2 + phic4 - 2*phik + mufactor*((phic2 + phic4 - phi(k-1,0,j+1) - phi(k-1,0,j-1))*invdt - 2*phidt))*dy2)
                       * dt*dt*c2*invdxdy + 2*phik-phi(k-1,0,j);
        phi.Normal(k+1,0,j) = TGVectorF4( -(phic2 - phic4)*0.5*invdx,-(phic1 - phik)*invdy, 1, 0);
    }

    // i = 0, j = w-1
    {
        const real phidt = (phi(k,0,w-1) - phi(k-1,0,w-1))*invdt;
        const real phik = phi(k,0,w-1);
        const real phic1 = phi(k,0+1,w-1);
        const real phic4 = phi(k,0,w-1-1);
        phi(k+1,0,w-1) = ((phic1- phik + mufactor*((phic1 - phi(k-1,0+1,w-1))*invdt - phidt))*dx2 +
                       (phic4 - phik + mufactor*((phic4 - phi(k-1,0,w-1-1))*invdt - phidt))*dy2)
                       * dt*dt*c2*invdxdy + 2*phik-phi(k-1,0,w-1);
        phi.Normal(k+1,0,w-1) = TGVectorF4( -(phik - phic4)*invdx,-(phic1 - phik)*invdy, 1, 0);
    }

    //i = h-1; j = 0
    {
        const real phidt = (phi(k,h-1,0) - phi(k-1,h-1,0))*invdt;
        const real phik = phi(k,h-1,0);
        const real phic2 = phi(k,h-1,0+1);
        const real phic3 = phi(k,h-1-1,0);
        phi(k+1,h-1,0) = ((phic3 - phik + mufactor*((phic3 - phi(k-1,h-1-1,0))*invdt - phidt))*dx2 +
                       (phic2 - phik + mufactor*((phic2 - phi(k-1,h-1,0+1))*invdt - phidt))*dy2)
                       * dt*dt*c2*invdxdy + 2*phik-phi(k-1,h-1,0);
        phi.Normal(k+1,h-1,0) = TGVectorF4( -(phic2 - phik)*invdx,-(phik - phic3)*invdy, 1, 0);
    }

    //i = h-1; j = ...
    for(uint j = 1; j < w-1; j++)
    {
        const real phidt = (phi(k,h-1,j) - phi(k-1,h-1,j))*invdt;
        const real phik = phi(k,h-1,j);
        const real phic2 = phi(k,h-1,j+1);
        const real phic3 = phi(k,h-1-1,j);
        const real phic4 = phi(k,h-1,j-1);
        phi(k+1,h-1,j) = ((phic3 - phik + mufactor*((phic3 - phi(k-1,h-1-1,j))*invdt - phidt))*dx2 +
                       (phic2 + phic4 - 2*phik + mufactor*((phic2 + phic4 - phi(k-1,h-1,j+1) - phi(k-1,h-1,j-1))*invdt - 2*phidt))*dy2)
                       * dt*dt*c2*invdxdy + 2*phik-phi(k-1,h-1,j);
        phi.Normal(k+1,h-1,j) = TGVectorF4( -(phic2 - phic4)*0.5*invdx,-(phik - phic3)*invdy, 1, 0);
    }

    //i = h-1; j = w-1
    {
        const real phidt = (phi(k,h-1,w-1) - phi(k-1,h-1,w-1))*invdt;
        const real phik = phi(k,h-1,w-1);
        const real phic3 = phi(k,h-1-1,w-1);
        const real phic4 = phi(k,h-1,w-1-1);
        phi(k+1,h-1,w-1) = ((phic3 - phik + mufactor*((phic3 - phi(k-1,h-1-1,w-1))*invdt - phidt))*dx2 +
                       (phic4 - phik + mufactor*((phic4 - phi(k-1,h-1,w-1-1))*invdt - phidt))*dy2)
                       * dt*dt*c2*invdxdy + 2*phik-phi(k-1,h-1,w-1);
        phi.Normal(k+1,h-1,w-1) = TGVectorF4( -(phik - phic4)*invdx,-(phik - phic3)*invdy, 1, 0);
    }

    //i = ...; j = 0
    for(uint i = 1; i < h-1; i++)
    {
        const real phidt = (phi(k,i,0) - phi(k-1,i,0))*invdt;
        const real phik = phi(k,i,0);
        const real phic1 = phi(k,i+1,0);
        const real phic2 = phi(k,i,0+1);
        const real phic3 = phi(k,i-1,0);
        phi(k+1,i,0) = ((phic1 + phic3 - 2*phik + mufactor*((phic1 + phic3 - phi(k-1,i+1,0) - phi(k-1,i-1,0))*invdt - 2*phidt))*dx2 +
                       (phic2 - phik + mufactor*((phic2 - phi(k-1,i,0+1))*invdt - phidt))*dy2)
                       * dt*dt*c2*invdxdy + 2*phik-phi(k-1,i,0);
        phi.Normal(k+1,i,0) = TGVectorF4( -(phic2 - phik)*invdx,-(phic1 - phic3)*0.5*invdy, 1, 0);
    }

    //i = ...; j = w-1
    for(uint i = 1; i < h-1; i++)
    {
        const real phidt = (phi(k,i,w-1) - phi(k-1,i,w-1))*invdt;
        const real phik = phi(k,i,w-1);
        const real phic1 = phi(k,i+1,w-1);
        const real phic3 = phi(k,i-1,w-1);
        const real phic4 = phi(k,i,w-1-1);
        phi(k+1,i,w-1) = ((phic1 + phic3 - 2*phik + mufactor*((phic1 + phic3 - phi(k-1,i+1,w-1) - phi(k-1, i-1,w-1))*invdt - 2*phidt))*dx2 +
                       (phic4 - phik + mufactor*((phic4 - phi(k-1,i,w-1-1))*invdt - phidt))*dy2)
                       * dt*dt*c2*invdxdy + 2*phik-phi(k-1,i,w-1);
        phi.Normal(k+1,i,w-1) = TGVectorF4( -(phik - phic4)*invdx,-(phic1 - phic3)*0.5*invdy, 1, 0);
    }
}
