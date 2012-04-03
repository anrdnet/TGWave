
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
    uint myWidth;
    uint myHeight;
    GLint myViewport[4];
    GLuint myTexture;
    GLuint myFrameBuffer;

    public:
    TGRenderManager();
    ~TGRenderManager();
    void Create();
    
    void ChangeSize(uint width, uint height);

    void BeginEnv(GLenum face);
    GLuint EndEnv();
};

#endif
