
#include <string>
#include "visual/TGCamera.h"
#include "core/TGMatrix.h"

void TGCamera::Create()
{
    TGVectorF4 dir = myPosition - myLookAt; 
    Debug("Dir is: "<<(string)dir);
    dir.Normalize();
    Debug("Dir is: "<<(string)dir);
    myView = TGMatrix4();
    myView(0,3) = -myPosition.X;
    myView(1,3) = -myPosition.Y;
    myView(2,3) = -myPosition.Z;

    if(abs(dir.Y) < 0.9)
    {
        Debug("Using 3D view");
        TGVectorF4 X = UnitYF % dir;
        TGVectorF4 Y = dir % X;
        myView(2,0) = dir.X;
        myView(2,1) = dir.Y;
        myView(2,2) = dir.Z;
        myView(0,0) = X.X;
        myView(0,1) = X.Y;
        myView(0,2) = X.Z;
        myView(1,0) = Y.X;
        myView(1,1) = Y.Y;
        myView(1,2) = Y.Z;
    }
    else
    {
        Debug("Using 2D view");
        myView(2,0) = 0;
        myView(2,1) = 1;
        myView(2,2) = 0;
        myView(1,0) = 0;
        myView(1,1) = 0;
        myView(1,2) = 1;
    }
}

TGVectorF4 &TGCamera::Move(TGVectorF4 &offset)
{
    myPosition += offset;
    Create();
    return myPosition;
}
