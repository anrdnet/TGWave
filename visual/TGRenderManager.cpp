
#include "visual/TGRenderManager.h"
#include "core/TGDebug.h"

TGRenderManager::TGRenderManager()
{
    myWidth=2048;
    myHeight=2048;
    myViewport[3] = 0;
}

TGRenderManager::~TGRenderManager()
{
    if(glIsFramebuffer(myFrameBuffer))
        glDeleteFramebuffers(1, &myFrameBuffer);
    if(glIsTexture(myTexture))
        glDeleteTextures(1, &myTexture);
}

void TGRenderManager::Create()
{
    glGenFramebuffers(1, &myFrameBuffer);
    CheckError();
    glGenTextures(1, &myTexture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, myTexture);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA, myWidth, myHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    CheckError();
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA, myWidth, myHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA, myWidth, myHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA, myWidth, myHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA, myWidth, myHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA, myWidth, myHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    CheckError();
}


void TGRenderManager::BeginEnv(GLenum face)
{
    glBindFramebuffer(GL_FRAMEBUFFER, myFrameBuffer);
    CheckError();
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, face, myTexture, 0);
    if(myViewport[3] == 0)
        glGetIntegerv(GL_VIEWPORT, myViewport);
    glViewport(0,0,myWidth,myHeight);
    CheckError();
    Bug(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE, "Framebuffer incomplete");
    CheckError();
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

GLuint TGRenderManager::EndEnv()
{
    //glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, 0, 0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, myTexture);
    glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(myViewport[0],myViewport[1],myViewport[2],myViewport[3]);
    myViewport[3] = 0;
    glClearColor(0.1,0.1,0.1,1);
    return myTexture;
}
