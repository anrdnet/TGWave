
#include "visual/TGShader.h"
#include "core/TGDebug.h"

TGShader::TGShader()
{
    myShaders[0] = 0;
    myShaders[1] = 0;
}

TGShader::~TGShader()
{
    Debug("Deleting shader");
    for(int i = 0; i < 2; i++)
    {
        if(myShaders[i] != 0)
        {
            if(glIsShader(myShaders[i]))
            {
                glDetachShader(myProgram, myShaders[i]);
                glDeleteShader(myShaders[i]);
            }
        }
    }
    if(glIsProgram(myProgram))
        glDeleteProgram(myProgram);
}

void TGShader::Create()
{
    this->TGShader::~TGShader();
    myProgram = glCreateProgram();
    myShaders[0] = 0;
    myShaders[1] = 0;
}

void TGShader::SetTransform(const TGMatrix4 &matrix)
{
    glUniformMatrix4fv(myTransformLoc, 1, GL_FALSE, matrix);
    CheckError();
}

void TGShader::SetUniformf(const char *name, float value)
{
    GLint loc = glGetUniformLocation(myProgram, name);
    CheckError();
    Debug("Uniform %d is %s", loc, name);
    Bug(loc == -1, "Uniform not found");
    glUniform1f(loc, value);
    CheckError();
}

void TGShader::SetShader(TGShaderType type, const char *shaderCode)
{
    if(myShaders[type] != 0)
    {
        Debug("Shader existed, delete it");
        glDetachShader(myProgram, myShaders[type]);
        glDeleteShader(myShaders[type]);
        CheckError();
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
            Bug(true, "Unknown shader type");
    }

    myShaders[type] = glCreateShader(shaderType);

    const char *source = shaderCode;
    glShaderSource(myShaders[type], 1, &source, NULL);
    CheckError();
    glCompileShader(myShaders[type]);
    CheckError();
    GLint status;
    glGetShaderiv(myShaders[type], GL_COMPILE_STATUS, &status);
    if(status != GL_TRUE)
    {
        Debug("##DEBUG##%s##DEBUG##",shaderCode);
        glGetShaderiv(myShaders[type], GL_INFO_LOG_LENGTH, &status);
        Bug(status == 0, "Unknown compile error");
        char *buffer = new char[status+1];
        GLsizei length;
        glGetShaderInfoLog(myShaders[type], status, &length, buffer);
        buffer[length] = 0;
        Debug("Error: %s", buffer);
        Bug(true, "Compilation failed:");
        delete [] buffer;
    }
    CheckError();

    glAttachShader(myProgram, myShaders[type]);
    CheckError();

}

void TGShader::Link()
{
    glLinkProgram(myProgram);
    int status;
    glGetProgramiv(myProgram, GL_LINK_STATUS, &status);
    if(status != GL_TRUE)
    {
        glGetProgramiv(myProgram, GL_INFO_LOG_LENGTH, &status);
        Bug(status == 0, "Unknown link error");
        char *buffer = new char[status+1];
        GLsizei length;
        glGetProgramInfoLog(myProgram, status, &length, buffer);
        buffer[length] = 0;
        Debug("Error: %s", buffer);
        Bug(true, "Compilation failed:");
        delete [] buffer;
    }
    myTransformLoc = glGetUniformLocation(myProgram, "Transform");
    CheckError();
}

void TGShader::Use()
{
    glUseProgram(myProgram);
}

void TGShader::SetAttribute(const char *name, GLuint vbo, uint elementCount,
        GLenum type, uint stride, uint offset, uint divisor)
{
    GLuint attribute = glGetAttribLocation(myProgram, name);
    CheckError();
    glEnableVertexAttribArray(attribute);
    CheckError();
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    CheckError();
    glVertexAttribPointer(attribute, elementCount, type, GL_FALSE, stride, (char*)NULL+offset);
    CheckError();
}
