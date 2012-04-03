
#ifndef TGCAMERA_H_
#define TGCAMERA_H_

#include "core/TGMatrix.h"
#include "core/TGVector.h"
#include "core/TGDebug.h"

class TGCamera
{
    TGMatrix4 myView;
    TGMatrix4 myProjection;
    TGMatrix4 my2DProjection;
    TGVectorF4 myLookAt;
    TGVectorF4 myPosition;
    void Create();
    bool my2D;
    public:
    TGVectorF4 &Move(TGVectorF4 &offset);
    TGVectorF4 &Orbit(real az, real el);
    TGVectorF4 &Zoom(real factor);

    TGMatrix4 &GetView()
    {
        return myView;
    }

    TGMatrix4 &GetProjection()
    {
        if(my2D)
            return my2DProjection;
        return myProjection;
    }

    TGVectorF4 GetPosition() 
    {
        if(my2D)
            return myLookAt + TGVectorF4(0,5,0);
        return myPosition;
    }

    void SetPosition(const TGVectorF4 &pos)
    {
        myPosition = pos;
        Create();
    }

    void SetOrientation(real az, real el);

    void LookAt(const TGVectorF4 &la)
    {
        myLookAt = la;
        Create();
    }

    TGVectorF4 GetViewDirection()
    {
        return TGVectorF4(-myView(2,0), -myView(2,1), -myView(2,2));
    }

    void MakeProjection(real width, real height);
};

#endif
