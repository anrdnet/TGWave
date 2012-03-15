
#include "visual/TGShader.h"
#include "core/TGError.h"

TGShader::TGShader()
{
    myProgram = glCreateProgram();
    myShaders[0] = 0;
    myShaders[1] = 0;
}

TGShader::~TGShader()
{
    for(int i = 0; i < 2; i++)
    {
        if(myShaders[i] != 0)
        {
            glDetachShader(myProgram, myShaders[i]);
            glDeleteShader(myShaders[i]);
        }
    }
    glDeleteProgram(myProgram);
}

void TGShader::SetShader(TGShaderType type, const string shaderCode)
{
    if(myShaders[type] != 0)
    {
        glDetachShader(myProgram, myShaders[type]);
        glDeleteShader(myShaders[type]);
    }

    GLenum shaderType;
    switch(type)
    {
        case TGVertexShader:
            shaderType = GL_VERTEX_SHADER;
            break;
        case TGFragmentShader:
            shaderType = GL_FRAGMENT_SHADER;
            break;
        default:
            throw TGError("Unknown shader type");
    }

    myShaders[type] = glCreateShader(shaderType);

    const char *source = shaderCode.c_str();
    glShaderSource(myShaders[type], 1, &source, NULL);
    glCompileShader(myShaders[type]);
    GLint status;
    glGetShaderiv(myShaders[type], GL_COMPILE_STATUS, &status);
    if(status != GL_TRUE)
    {
        glGetShaderiv(myShaders[type], GL_INFO_LOG_LENGTH, &status);
        if(status == 0)
            throw TGError("Unknown compile error");
        char *buffer = new char[status+1];
        GLsizei length;
        glGetShaderInfoLog(myShaders[type], status, &length, buffer);
        buffer[length] = 0;
        string log(buffer);
        delete [] buffer;
        throw TGError("Compilation failed:\n"+log);
    }

    glAttachShader(myProgram, myShaders[type]);
}

void TGShader::Link()
{
    glLinkProgram(myProgram);
    int status;
    glGetProgramiv(myProgram, GL_LINK_STATUS, &status);
    if(status != GL_TRUE)
    {
        glGetProgramiv(myProgram, GL_INFO_LOG_LENGTH, &status);
        if(status == 0)
            throw TGError("Unknown link error");
        char *buffer = new char[status+1];
        GLsizei length;
        glGetProgramInfoLog(myProgram, status, &length, buffer);
        buffer[length] = 0;
        string log(buffer);
        delete [] buffer;
        throw TGError("Linking failed:\n"+log);
    }
}

void TGShader::Use()
{
    glUseProgram(myProgram);
}

void TGShader::SetAttribute(string name, GLuint vbo, uint elementCount,
        GLenum type, uint stride, uint offset, uint divisor)
{
    GLuint attribute = glGetAttribLocation(myProgram, name.c_str());
    glEnableVertexAttribArray(attribute);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(attribute, elementCount, type, GL_FALSE, stride, (char*)NULL+offset);
    if(divisor != 0)
        glVertexAttribDivisor(attribute, divisor);
}
