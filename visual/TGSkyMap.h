
#ifndef TGSKYMAP_H_
#define TGSKYMAP_H_
#include "core/TGDef.h"
#include "visual/TGShader.h"

class TGSkyMap
{
    enum
    {
        VBO,
        TexCoord,
        Element
    };
    GLuint myTexture;
    GLuint myBuffers[3];

    real mySize;
    TGVectorF4 myCenter;

    public:
    TGSkyMap(real size, const TGVectorF4 &center);
    ~TGSkyMap();
    void Create(const char *skymapFile);

    void Draw(TGShader &shader, bool setTex = true);
};

#endif
