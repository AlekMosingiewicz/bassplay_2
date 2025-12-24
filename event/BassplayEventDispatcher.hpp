//
// Created by aleksander on 25.02.24.
//

#ifndef BASSPLAY_2_BASSPLAYEVENTDISPATCHER_HPP
#define BASSPLAY_2_BASSPLAYEVENTDISPATCHER_HPP

#include <map>
#include <string>
#include <list>
#include "IBassplayEventHandler.hpp"
#include "BassplayEventType.hpp"

namespace Bassplay::Event {

    typedef std::list<IBassplayEventHandler *> EventHandlerList;

    class BassplayEventDispatcher {
    public:
        static BassplayEventDispatcher &Instance();

        void RegisterHandler(BassplayEventType type, IBassplayEventHandler *handler);

        template<class T>
        void BroadcastEvent(T &event) {
            BassplayEventType type = event.GetType();
            if (!HasListenersForEvent(type)) {
                return;
            }
            auto handlers = *m_EventHandlers[type];
            for (auto *handler: handlers) {
                handler->Handle(event);
            }
        };

    private:
        BassplayEventDispatcher() = default;

        std::map<BassplayEventType, EventHandlerList *> m_EventHandlers;

        bool HasListenersForEvent(BassplayEventType type);

        void ClearHandlersForEvent(BassplayEventType type);

        ~BassplayEventDispatcher();
    };

}

#endif //BASSPLAY_2_BASSPLAYEVENTDISPATCHER_HPP
