
#ifndef ANMESSAGEPUMP_H_
#define ANMESSAGEPUMP_H_

#include "core/ANDef.h"
#include "core/ANMessageHandler.h"
#include "core/ANError.h"
#include <deque>

class ANMessagePump
{
    bool myRunning;
    deque<ANMessageHandler*> myHandlers;

    public:
    ANMessagePump()
        : myRunning(false) { }
    bool Run() throw(ANError);

    void AddHandler(ANMessageHandler *handler);
};

#endif
