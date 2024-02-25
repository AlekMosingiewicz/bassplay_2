//
// Created by aleksander on 25.02.24.
//

#ifndef BASSPLAY_2_BASSPLAYEVENT_H
#define BASSPLAY_2_BASSPLAYEVENT_H

#include "BassplayEventType.h"

namespace Bassplay::Event {
    class BassplayEvent {
    public:
        explicit BassplayEvent(BassplayEventType eventType): m_eventType(eventType) {};
    protected:
        BassplayEventType m_eventType;
    };
}



#endif //BASSPLAY_2_BASSPLAYEVENT_H
