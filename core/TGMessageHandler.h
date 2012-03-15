#ifndef TGMESSAGEHTGDLER_H_
#define TGMESSAGEHTGDLER_H_

#include <SDL/SDL.h>

class TGMessageHandler
{
    public:
    virtual bool HandleMessage(SDL_Event &message) = 0;
};

#endif
