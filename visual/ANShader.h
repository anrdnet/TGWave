
#ifndef ANSHADER_H_
#define ANSHADER_H_

#include "core/ANDef.h"
#include <string>

using namespace std;

enum ANShaderType
{
    ANVertexShader = 0,
    ANFragmentShader = 1
};

class ANShader
{
    uint myProgram;
    uint myShaders[2];

    public:
    ANShader();
    ~ANShader();

    void SetShader(ANShaderType, const string shaderCode);
    void Link();
    void Use();

    void SetAttribute(string name, GLuint vbo, uint elementCount, GLenum type, uint stride, uint offset, uint divisor = 0);
};

#endif
