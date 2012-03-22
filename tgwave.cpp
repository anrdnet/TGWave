
#include <iostream>
#include "visual/TGRender.h"
#include "core/TGResourceManager.h"
#include "TGInterface.h"
#include <SDL/SDL.h>
#include <cmath>

int main(int argc, char *argv[])
{
    Initialize();
    TGRender render(0,0);

    TGResourceManager rec;
    TGResource vs = rec.CreateResource(TGResourceType::Shader, "cubeshader.vs");
    TGResource fs = rec.CreateResource(TGResourceType::Shader, "cubeshader.fs");
    TGResource bfs = rec.CreateResource(TGResourceType::Shader, "black.fs");
    Debug("Got shaders");
    Create(rec.GetData(vs).c_str(), rec.GetData(fs).c_str(), rec.GetData(bfs).c_str());

    ChangeSize(render.GetSize().Width, render.GetSize().Height);
    bool running = true;
    Touch(700, 370);
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
                    ChangeSize(event.resize.w, event.resize.h);
                    break;
                default:
                    break;
            }
        }
        Draw();
        
        render.Present();
    }
}
