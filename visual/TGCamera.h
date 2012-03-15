
#ifndef TGCAMERA_H_
#define TGCAMERA_H_

#include "core/TGMatrix.h"
#include "core/TGVector.h"
#include "core/TGDebug.h"

class TGCamera
{
    TGMatrix4 myView;
    TGVectorF4 myLookAt;
    TGVectorF4 myPosition;
    void Create();
    public:
    TGVectorF4 &Move(TGVectorF4 &offset);
    TGVectorF4 &Orbit(real az, real el);
    TGVectorF4 &Zoom(real factor);
    TGMatrix4 &GetView()
    {
        return myView;
    }
    TGVectorF4 GetPosition() 
    {
        return myPosition;
    }

    void SetPostition(const TGVectorF4 &pos)
    {
        myPosition = pos;
        Create();
    }

    void SetOrientation(real az, real el);

    void LookAt(const TGVectorF4 &la)
    {
        myLookAt = la;
    }

    TGVectorF4 GetViewDirection()
    {
        return TGVectorF4(-myView(2,0), -myView(2,1), -myView(2,2));
    }
};

#endif
