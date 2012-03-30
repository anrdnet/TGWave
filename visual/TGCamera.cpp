
#include "visual/TGCamera.h"
#include "core/TGMatrix.h"
#include <cmath>

void TGCamera::Create()
{
    TGVectorF4 dir = myPosition - myLookAt; 
    TGVectorF4 Z = dir;
    Z.Normalize();
    myView = TGMatrix4();
    TGVectorF4 X;
    TGVectorF4 Y;

    if(fabsf(Z.Y) < 0.9)
    {
        //Debug("Using 3D view, %g", fabsf(Z.Y));
        X = UnitYF % Z;
        X.Normalize();
        Y = Z % X;
        myView(0,3) = -(myPosition * X);
        myView(1,3) = -(myPosition * Y);
        myView(2,3) = -(myPosition * Z);
        my2D = false;
    }
    else
    {
        //Debug("Using 2D view");
        X = UnitXF;
        Y = ZeroF-UnitZF;
        Z = UnitYF;
        myView(0,3) = -myLookAt.X;
        myView(1,3) = myLookAt.Z;
        myView(2,3) = -(myPosition * UnitYF);
        my2D = true;
        myPosition.Z = myLookAt.Z + sqrtf(dir.X*dir.X+dir.Z * dir.Z);
        myPosition.X = myLookAt.X;
    }
    myView(2,0) = Z.X;
    myView(2,1) = Z.Y;
    myView(2,2) = Z.Z;
    myView(0,0) = X.X;
    myView(0,1) = X.Y;
    myView(0,2) = X.Z;
    myView(1,0) = Y.X;
    myView(1,1) = Y.Y;
    myView(1,2) = Y.Z;
}

TGVectorF4 &TGCamera::Move(TGVectorF4 &offset)
{
    myPosition += offset;
    Create();
    return myPosition;
}

TGVectorF4 &TGCamera::Orbit(real az, real el)
{
    //Debug("Rotate az: %g; el: %g", az, el);
    TGVectorF4 dir = myPosition - myLookAt;
    TGVectorF4 lX = TGVectorF4(myView(0,0), myView(0,1), myView(0,2));
    lX.Normalize();

    dir = dir*cos(-el) + (lX%dir)*sin(-el)+lX*(lX*dir)*(1-cos(-el));
    real cosa = cos(az);
    real sina = sin(az);
    dir.X = dir.X*cosa - dir.Z * sina;
    dir.Z = dir.X*sina + dir.Z * cosa;
    myPosition = myLookAt + dir;

    Create();
    return myPosition;
}

TGVectorF4 &TGCamera::Zoom(real factor)
{
    TGVectorF4 dir = myPosition - myLookAt;
    dir*=factor;
    
    myPosition = myLookAt + dir;

    Create();
    return myPosition;
}

void TGCamera::MakeProjection(real width, real height)
{
    real ratio = width / height;
    myProjection.CreatePerspective(3.14/4, ratio, 0.1, 50);
    my2DProjection.CreateOrthogonal(-ratio,ratio,-1,1, 0.1, 50);
}
