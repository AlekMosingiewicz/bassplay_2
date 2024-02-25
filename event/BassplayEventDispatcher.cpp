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
    BassplayEventDispatcher::RegisterHandler(const std::string &name, IBassplayEventHandler *handler) {
        if (!HasListenersForEvent(name)) {
            m_EventHandlers[name] = new EventHandlerList();
        }
        m_EventHandlers[name]->push_back(handler);
    }

    bool BassplayEventDispatcher::HasListenersForEvent(const std::string &name) {
        return dynamic_cast<EventHandlerList *>(m_EventHandlers[name]) != nullptr;
    }

    void
    BassplayEventDispatcher::BroadcastEvent(const std::string &name, Bassplay::Event::BassplayEvent event) {
        if (!HasListenersForEvent(name)) {
            return;
        }
        auto handlers = *m_EventHandlers[name];
        for (auto *handler: handlers) {
            handler->Handle(event);
        }
    }

    void BassplayEventDispatcher::ClearHandlersForEvent(const std::string &name) {
        if (!HasListenersForEvent(name)) {
            return;
        }
        auto handlers = *m_EventHandlers[name];
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