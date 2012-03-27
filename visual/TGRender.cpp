
#include "TGRender.h"

void TGRender::Initialize(int width, int height, bool fullscreen) throw(TGError)
{
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_NOPARACHUTE) != 0)
        throw TGError(SDL_GetError()).Prepend(TGErrorCode::SdlInit);

    const SDL_VideoInfo *vinfo = SDL_GetVideoInfo();

    if(vinfo == NULL)
        throw TGError(SDL_GetError()).Prepend(TGErrorCode::SdlVideoInfoNull);

    byte bpp = vinfo->vfmt->BitsPerPixel;

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    if(!(myScreen = SDL_SetVideoMode(width, height, bpp, SDL_OPENGL | (fullscreen ? SDL_FULLSCREEN : SDL_RESIZABLE))))
    {
        throw TGError(SDL_GetError()).Prepend(TGErrorCode::SdlInitWindow);
    }

    myCurrentSize.Height = myScreen->h;
    myCurrentSize.Width = myScreen->w;

    Debug("Context successfully created");
}

TGRender::TGRender() throw(TGError)
{
    Initialize(0, 0, true);
    InitDefState();
}

TGRender::TGRender(int width, int height) throw(TGError)
{
    Initialize(width, height, false);
    InitDefState();
}

TGRender::~TGRender()
{
    SDL_Quit();
    Debug("Context destroyd");
}

void TGRender::InitDefState()
{
    //glClearColor(100.0/256,149.0/256,237.0/256,1);
    //glClear(GL_COLOR_BUFFER_BIT);
    //glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
}

void TGRender::Resize(uint width, uint height)
{
    if(!(myScreen = SDL_SetVideoMode(width, height, 0, SDL_OPENGL | SDL_RESIZABLE)))
    {
        throw TGError(SDL_GetError()).Prepend(TGErrorCode::SdlInitWindow);
    }

    myCurrentSize.Height = myScreen->h;
    myCurrentSize.Width = myScreen->w;
}
