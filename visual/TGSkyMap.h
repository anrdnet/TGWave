
#ifndef TGSKYMAP_H_
#define TGSKYMAP_H_
#include "core/TGDef.h"
#include "visual/TGShader.h"

class TGSkyMap
{
    enum
    {
        VBO,
        Element
    };
    GLuint myTexture;
    GLuint myBuffers[2];

    real mySize;
    TGVectorF4 myCenter;
    bool own;

    public:
    TGSkyMap(real size, const TGVectorF4 &center);
    ~TGSkyMap();
    void Create(const char *skymapFile);
    void SetTexture(GLuint texture)
    {
        if(glIsTexture(myTexture) && own)
            glDeleteTextures(1, &myTexture);
        own = false;
        myTexture = texture;
    }
    GLuint GetTexture()
    {
        return myTexture;
    }

    void Draw(TGShader &shader, bool setTex = true);
};

#endif
