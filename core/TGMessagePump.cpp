
#include "core/TGMessagePump.h"

bool TGMessagePump::Run() throw(TGError)
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
                    deque<TGMessageHandler*>::iterator it;
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

void TGMessagePump::AddHandler(TGMessageHandler *handler)
{
    if(!myRunning)
        myHandlers.push_back(handler);
}
