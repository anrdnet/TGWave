
#include <iostream>
#include <SDL/SDL.h>
#include <cmath>
#include "visual/TGRender.h"
#include "core/TGResourceManager.h"
#include "TGInterface.h"
#include "TGSettingsGUI.h"

struct StartInfo
{
    int argc;
    char **argv;
    SimParams &Params;
    StartInfo(int margc, char **margv, SimParams &mParams)
        : argc(margc), argv(margv), Params(mParams) { }
};

int StartGUI(void *start)
{
    StartInfo *info = static_cast<StartInfo*>(start);
    TGSettingsGUI::RunGUI(info->argc, info->argv, info->Params);
    delete info;
    return 0;
}

int main(int argc, char *argv[])
{
    if(pthread_mutex_init(&SimParams::Lock, NULL) != 0)
        Bug(true, "Failed to make mutex");
    SimParams &params = Initialize();
    TGRender render(0,0);

    StartInfo *info = new StartInfo(argc, argv, params);
    SDL_Thread *guiThread = SDL_CreateThread(&StartGUI, info);

    TGResourceManager rec;
    TGResource vs = rec.CreateResource(TGResourceType::Shader, "cubeshader.vs");
    TGResource fs = rec.CreateResource(TGResourceType::Shader, "cubeshader.fs");
    TGResource bfs = rec.CreateResource(TGResourceType::Shader, "black.fs");
    Debug("Got shaders");
    Create(rec.GetData(vs).c_str(), rec.GetData(fs).c_str(), rec.GetData(bfs).c_str());

    ChangeSize(render.GetSize().Width, render.GetSize().Height);
    bool running = true;
    
    bool mouse1Down = false;
    bool mouse2Down = false;
    bool click = false;

    while(running)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_VIDEORESIZE:
                    render.Resize(event.resize.w, event.resize.h);
                    ChangeSize(event.resize.w, event.resize.h);
                    break;
                case SDL_MOUSEMOTION:
                    click = false;
                    //Debug("Got mouse move with dx=%d, dy=%d", event.motion.xrel, event.motion.yrel);
                    if(mouse1Down)
                        Orbit(event.motion.xrel, event.motion.yrel);
                    else if (mouse2Down)
                        Zoom((event.motion.yrel)*0.01 + 1);
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    //Debug("Got mouse down on button %d", event.button.button);
                    if(event.button.button == 1)
                    {
                        click = true;
                        mouse1Down = true;
                    }
                    else if(event.button.button == 3)
                        mouse2Down = true;
                    break;
                case SDL_MOUSEBUTTONUP:
                    //Debug("Got mouse up on button %d", event.button.button);
                    if(event.button.button == 1)
                        mouse1Down = false;
                    else if(event.button.button == 3)
                        mouse2Down = false;

                    if(click)
                    {
                        Touch(event.button.x, event.button.y);
                        click = false;
                    }
                    break;
                default:
                    break;
            }
        }
        Draw();
        
        render.Present();
    }

    if(pthread_mutex_destroy(&SimParams::Lock) != 0)
        Bug(true, "Failed to destroy mutex");
    return 0;
}
