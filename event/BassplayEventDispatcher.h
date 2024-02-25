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

        void RegisterHandler(const std::string &name, IBassplayEventHandler *handler);

        void BroadcastEvent(const std::string &name, BassplayEvent event);

    private:
        BassplayEventDispatcher() = default;

        std::map<std::string, EventHandlerList *> m_EventHandlers;

        bool HasListenersForEvent(const std::string &name);

        void ClearHandlersForEvent(const std::string &name);

        ~BassplayEventDispatcher();
    };

}

#endif //BASSPLAY_2_BASSPLAYEVENTDISPATCHER_H
