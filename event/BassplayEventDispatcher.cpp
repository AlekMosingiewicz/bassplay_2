//
// Created by aleksander on 25.02.24.
//

#include "BassplayEventDispatcher.h"

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

    void
    BassplayEventDispatcher::BroadcastEvent(BassplayEvent event) {
        BassplayEventType type = event.GetType();
        if (!HasListenersForEvent(type)) {
            return;
        }
        auto handlers = *m_EventHandlers[type];
        for (auto *handler: handlers) {
            handler->Handle(event);
        }
    }

    void BassplayEventDispatcher::ClearHandlersForEvent(BassplayEventType type) {
        if (!HasListenersForEvent(type)) {
            return;
        }
        auto handlers = *m_EventHandlers[type];
        for (auto *handler: handlers) {
            handlers.remove(handler);
            delete handler;
        }
    }

    BassplayEventDispatcher::~BassplayEventDispatcher() {
        auto events = m_EventHandlers;
        for (auto it = events.begin(); it != events.end(); it++) {
            ClearHandlersForEvent(it->first);
        }
    }
}