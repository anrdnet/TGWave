
#ifndef ANRENDER_H_
#define ANRENDER_H_

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <GL/gl.h>
#include <SDL/SDL.h>
#include "core/ANDef.h"
#include "core/ANError.h"
#include "core/ANDebug.h"
#include "core/ANMessageHandler.h"
#include "core/ANMatrix.h"

struct ANSizeInfo
{
    int Width;
    int Height;
};

class ANRender : public ANMessageHandler
{
    ANSizeInfo myCurrentSize;

    SDL_Surface *myScreen;

    void Initialize(int width, int height, bool fullscreen) throw(ANError);
    void InitDefState();
    public:
    ANRender() throw(ANError); 

    ANRender(int width, int height) throw(ANError);
    ~ANRender();

    virtual bool HandleMessage(SDL_Event &message);

    void SetProjection(ANSizeInfo &size);

    void Present()
    {
        SDL_GL_SwapBuffers();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    ANSizeInfo &GetSize()
    {
        return myCurrentSize;
    }
};

#endif
