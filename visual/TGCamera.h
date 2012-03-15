
#ifndef ANCAMERA_H_
#define ANCAMERA_H_

#include "core/ANMatrix.h"
#include "core/ANVector.h"
#include "core/ANDebug.h"

class ANCamera
{
    ANMatrix4 myView;
    ANVectorF4 myLookAt;
    ANVectorF4 myPosition;
    void Create();
    public:
    ANVectorF4 &Move(ANVectorF4 &offset);
    ANVectorF4 &Orbit(real az, real el);
    ANVectorF4 &Zoom(real factor);
    ANMatrix4 &GetView()
    {
        return myView;
    }
    ANVectorF4 GetPosition() 
    {
        return myPosition;
    }

    void SetPostition(ANVectorF4 &pos)
    {
        myPosition = pos;
        Create();
    }

    void SetOrientation(real az, real el);

    ANVectorF4 GetViewDirection()
    {
        return ANVectorF4(-myView(2,0), -myView(2,1), -myView(2,2));
    }
};

#endif
