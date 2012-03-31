
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
}

void TGRenderManager::ChangeSize(uint width, uint height)
{
    glBindTexture(GL_TEXTURE_2D, myTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    CheckError();
    glBindFramebuffer(GL_FRAMEBUFFER, myFrameBuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, myTexture, 0);
    Bug(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE, "Framebuffer incomplete");
    CheckError();
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    CheckError();
}

void TGRenderManager::BeginEnv()
{
    glBindFramebuffer(GL_FRAMEBUFFER, myFrameBuffer);
    glClear(GL_COLOR_BUFFER_BIT);
}

GLuint TGRenderManager::BeginWater()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    return myTexture;
}

void TGRenderManager::End()
{

}
