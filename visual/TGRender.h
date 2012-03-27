
#ifndef TGRENDER_H_
#define TGRENDER_H_

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <GL/gl.h>
#include <SDL/SDL.h>
#include "core/TGDef.h"
#include "core/TGError.h"
#include "core/TGDebug.h"
#include "core/TGMatrix.h"

struct TGSizeInfo
{
    int Width;
    int Height;
};

class TGRender
{
    TGSizeInfo myCurrentSize;

    SDL_Surface *myScreen;

    void Initialize(int width, int height, bool fullscreen) throw(TGError);
    void InitDefState();
    public:
    TGRender() throw(TGError); 

    TGRender(int width, int height) throw(TGError);
    ~TGRender();

    void Present()
    {
        SDL_GL_SwapBuffers();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    TGSizeInfo &GetSize()
    {
        return myCurrentSize;
    }
    void Resize(uint width, uint height);
};

#endif
