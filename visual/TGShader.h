
#ifndef TGSHADER_H_
#define TGSHADER_H_

#include "core/TGDef.h"
#include <string>

using namespace std;

enum TGShaderType
{
    TGVertexShader = 0,
    TGFragmentShader = 1
};

class TGShader
{
    uint myProgram;
    uint myShaders[2];

    public:
    TGShader();
    ~TGShader();

    void SetShader(TGShaderType, const string shaderCode);
    void Link();
    void Use();

    void SetAttribute(string name, GLuint vbo, uint elementCount, GLenum type, uint stride, uint offset, uint divisor = 0);
};

#endif
