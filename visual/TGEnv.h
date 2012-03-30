
#ifndef TGENV_H_
#define TGENV_H_

#include "core/TGDef.h"
#include "visual/TGShader.h"

class TGEnv
{
    enum BufferTypes
    {
        VBO,
        TexCoord,
        Element
    };
    GLuint myBuffers[3];

    public:
    TGEnv();
    ~TGEnv();
    void Create(real tw, real th, real border, real height, real depth);

    void Draw(TGShader &shader);
};

#endif
