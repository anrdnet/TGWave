
#include "visual/TGRenderManager.h"
#include "core/TGDebug.h"

TGRenderManager::TGRenderManager()
{

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
    uint width=1024;
    uint height=1024;
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    CheckError();
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    CheckError();
}


void TGRenderManager::BeginEnv(GLenum face)
{
    glBindFramebuffer(GL_FRAMEBUFFER, myFrameBuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, face, myTexture, 0);
    Bug(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE, "Framebuffer incomplete");
    CheckError();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

GLuint TGRenderManager::BeginWater()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    return myTexture;
}

void TGRenderManager::End()
{

}
