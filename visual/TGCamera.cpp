
#include <string>
#include "visual/ANCamera.h"

void ANCamera::Create()
{
    ANVectorF4 dir = myLookAt - myPosition;
    dir.Normalize();
    ANVectorF4 up;
    if((dir-UnitYF).Length() < 0.1)
    {
        myView(0,0) = 
    }
}

ANVectorF4 &ANCamera::Move(ANVectorF4 &offset)
{
    myPosition += offset;
    return myPosition;
}
