#ifndef ANMESSAGEHANDLER_H_
#define ANMESSAGEHANDLER_H_

#include <SDL/SDL.h>

class ANMessageHandler
{
    public:
    virtual bool HandleMessage(SDL_Event &message) = 0;
};

#endif
