
#ifndef TGSHADER_H_
#define TGSHADER_H_

#include "core/TGDef.h"
#include "GL/gl.h"
#include "core/TGMatrix.h"

using namespace std;

enum TGShaderType
{
    TGVertexShader = 0,
    TGFragmentShader = 1
};

class TGShader
{
    GLuint myTransformLoc;
    GLuint myNormalTransformLoc;
    uint myProgram;
    uint myShaders[2];

    public:
    TGShader();
    ~TGShader();

    void Create();

    void SetTransform(const TGMatrix4 &matrix);
    void SetUniformf(const char *name, float value);
    void SetUniformv4(const char *name, const TGVectorF4 &value);
    void SetTexture(const char *sampler, GLuint texture, int slot);

    void SetShader(TGShaderType, const char *shaderCode);
    void Link();
    void Use();

    void SetAttribute(const char *name, GLuint vbo, uint elementCount, GLenum type, uint stride, uint offset, uint divisor = 0);
};

#endif
