
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

    StartInfo *info = new StartInfo(argc, argv, params);
    SDL_Thread *guiThread = SDL_CreateThread(&StartGUI, info);

    TGRender render(0,0);
    TGResourceManager rec;
    TGResource vs = rec.CreateResource(TGResourceType::Shader, "water.vs");
    TGResource fs = rec.CreateResource(TGResourceType::Shader, "water.fs");
    TGResource bfs = rec.CreateResource(TGResourceType::Shader, "black.fs");
    TGResource envvs = rec.CreateResource(TGResourceType::Shader, "envshader.vs");
    TGResource envfs = rec.CreateResource(TGResourceType::Shader, "envshader.fs");
    TGResource colvs = rec.CreateResource(TGResourceType::Shader, "colors.vs");
    TGResource colfs = rec.CreateResource(TGResourceType::Shader, "colors.fs");
    TGResource cvs = rec.CreateResource(TGResourceType::Shader, "cube.vs");
    TGResource cfs = rec.CreateResource(TGResourceType::Shader, "cube.fs");
    Debug("Got shaders");
    Create(rec.GetData(vs).c_str(), rec.GetData(fs).c_str(), rec.GetData(bfs).c_str(), rec.GetData(envvs).c_str(), rec.GetData(envfs).c_str(),
            rec.GetData(colvs).c_str(), rec.GetData(colfs).c_str(), rec.GetData(cvs).c_str(), rec.GetData(cfs).c_str());

    ChangeSize(render.GetSize().Width, render.GetSize().Height);
    bool running = true;
    
    bool mouse1Down = false;
    int clickMovement = 0;

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
                    clickMovement += abs(event.motion.xrel) + abs(event.motion.yrel);
                    //Debug("Got mouse move with dx=%d, dy=%d", event.motion.xrel, event.motion.yrel);
                    if(mouse1Down)
                        Orbit(event.motion.xrel, event.motion.yrel);
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    Debug("Got mouse down on button %d", event.button.button);
                    if(event.button.button == 1)
                    {
                        clickMovement = 0;
                        mouse1Down = true;
                    }
                    break;
                case SDL_MOUSEBUTTONUP:
                    //Debug("Got mouse up on button %d", event.button.button);
                    if(event.button.button == 1)
                    {
                        if(clickMovement < 5)
                        {
                            Touch(event.button.x, event.button.y);
                        }
                        mouse1Down = false;
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
