//
// Created by aleksander on 25.02.24.
//

#include "BassplayEventDispatcher.hpp"

namespace Bassplay::Event {
    BassplayEventDispatcher &BassplayEventDispatcher::Instance() {
        static BassplayEventDispatcher instance;

        return instance;
    }

    void
    BassplayEventDispatcher::RegisterHandler(BassplayEventType type, IBassplayEventHandler *handler) {
        if (!HasListenersForEvent(type)) {
            m_EventHandlers[type] = new EventHandlerList();
        }
        m_EventHandlers[type]->push_back(handler);
    }

    bool BassplayEventDispatcher::HasListenersForEvent(BassplayEventType type) {
        return dynamic_cast<EventHandlerList *>(m_EventHandlers[type]) != nullptr;
    }

    void BassplayEventDispatcher::ClearHandlersForEvent(BassplayEventType type) {
        if (!HasListenersForEvent(type)) {
            return;
        }
        auto handlers = *m_EventHandlers[type];
        handlers.clear();
    }
}