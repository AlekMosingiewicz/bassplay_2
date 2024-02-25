//
// Created by aleksander on 25.02.24.
//

#ifndef BASSPLAY_2_BASSPLAYEVENTDISPATCHER_H
#define BASSPLAY_2_BASSPLAYEVENTDISPATCHER_H

#include <map>
#include <string>
#include <list>
#include "IBassplayEventHandler.h"
#include "BassplayEventType.h"

namespace Bassplay::Event {

    typedef std::list<IBassplayEventHandler *> EventHandlerList;

    class BassplayEventDispatcher {
    public:
        static BassplayEventDispatcher &Instance();

        void RegisterHandler(BassplayEventType type, IBassplayEventHandler *handler);

        void BroadcastEvent(BassplayEvent event);

    private:
        BassplayEventDispatcher() = default;

        std::map<BassplayEventType, EventHandlerList *> m_EventHandlers;

        bool HasListenersForEvent(BassplayEventType type);

        void ClearHandlersForEvent(BassplayEventType type);

        ~BassplayEventDispatcher();
    };

}

#endif //BASSPLAY_2_BASSPLAYEVENTDISPATCHER_H
