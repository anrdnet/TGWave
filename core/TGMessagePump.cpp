
#include "core/ANMessagePump.h"

bool ANMessagePump::Run() throw(ANError)
{
    myRunning = true;
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT:
                return false;
            default:
                {
                    deque<ANMessageHandler*>::iterator it;
                    for(it = myHandlers.begin(); it < myHandlers.end(); it++)
                    {
                        if((*it)->HandleMessage(event))
                            break;
                    }
                };
        }
    }
    myRunning = false;
    return true;
}

void ANMessagePump::AddHandler(ANMessageHandler *handler)
{
    if(!myRunning)
        myHandlers.push_back(handler);
}
