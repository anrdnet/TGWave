
#include <string>
#include "visual/TGCamera.h"
#include "core/TGMatrix.h"

void TGCamera::Create()
{
    TGVectorF4 Z =  myPosition - myLookAt; 
    Z.Normalize();
    Debug((string)Z);
    myView = TGMatrix4();
    TGVectorF4 X;
    TGVectorF4 Y;

    if(abs(Z.Y) < 0.9)
    {
        Debug("Using 3D view");
        X = UnitYF % Z;
        X.Normalize();
        Y = Z % X;
    }
    else
    {
        Debug("Using 2D view");
        X = UnitXF;
        Y = UnitZF;
        Z = UnitYF;
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
    myView(0,3) = -(myPosition * X);
    myView(1,3) = -(myPosition * Y);
    myView(2,3) = -(myPosition * Z);
}

TGVectorF4 &TGCamera::Move(TGVectorF4 &offset)
{
    myPosition += offset;
    Create();
    return myPosition;
}
