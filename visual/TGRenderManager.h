
#ifndef TGRENDERMANAGER_H_
#define TGRENDERMANAGER_H_

#include "core/TGDef.h"
#include "visual/TGShader.h"

class TGRenderManager
{
    enum
    {
        Frame = 0,
        Env = 1
    };
    GLuint myTextures[2];
    GLuint myFrameBuffer;

    TGShader &myEnvShader;
    TGShader &myWaterShader;

    public:
    TGRenderManager(TGShader &envShader, TGShader &waterShader);
    ~TGRenderManager();
    void Create();

    void BeginEnv();
    void BeginWater();
    void End();
};

#endif
