
#ifndef TGRENDERMANAGER_H_
#define TGRENDERMANAGER_H_

#include "core/TGDef.h"

class TGRenderManager
{
    enum
    {
        Frame = 0,
        Env = 1
    };
    GLuint myTexture;
    GLuint myFrameBuffer;

    public:
    TGRenderManager();
    ~TGRenderManager();
    void Create();
    
    void ChangeSize(uint width, uint height);

    void BeginEnv();
    GLuint BeginWater();
    void End();
};

#endif