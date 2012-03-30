
#include "visual/TGRenderManager.h"
#include "TilesTextureData.h"

TGRenderManager::TGRenderManager(TGShader &envShader, TGShader &waterShader)
    : myEnvShader(envShader), myWaterShader(waterShader)
{

}

TGRenderManager::~TGRenderManager()
{
    if(glIsFramebuffer(myFrameBuffer))
        glDeleteFramebuffers(1, &myFrameBuffer);
    if(glIsTexture(myTextures[0]))
        glDeleteTextures(2, myTextures);
}

byte pixeldata[] =
{
      0,  0,  0,    255,  0,  0,
      0,255,255,    255,255,255
};

void TGRenderManager::Create()
{
    glGenFramebuffers(1, &myFrameBuffer);
    CheckError();
    glGenTextures(2, myTextures);
    CheckError();
    glBindTexture(GL_TEXTURE_2D, myTextures[Env]);
    CheckError();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_UNSIGNED_BYTE, pixeldata);
    CheckError();
}

void TGRenderManager::BeginEnv()
{
    myEnvShader.Use();
    //glBindFramebuffer(GL_FRAMEBUFFER, myFrameBuffer);   
    myEnvShader.SetTexture("Tiles", myTextures[Env], 1);
    CheckError();
}

void TGRenderManager::BeginWater()
{
    myWaterShader.Use();
}

void TGRenderManager::End()
{

}
