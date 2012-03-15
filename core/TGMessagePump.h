
#ifndef TGMESSAGEPUMP_H_
#define TGMESSAGEPUMP_H_

#include "core/TGDef.h"
#include "core/TGMessageHandler.h"
#include "core/TGError.h"
#include <deque>

class TGMessagePump
{
    bool myRunning;
    deque<TGMessageHandler*> myHandlers;

    public:
    TGMessagePump()
        : myRunning(false) { }
    bool Run() throw(TGError);

    void AddHandler(TGMessageHandler *handler);
};

#endif
