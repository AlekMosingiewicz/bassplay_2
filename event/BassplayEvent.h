//
// Created by aleksander on 25.02.24.
//

#ifndef BASSPLAY_2_BASSPLAYEVENT_H
#define BASSPLAY_2_BASSPLAYEVENT_H

#include "BassplayEventType.h"

namespace Bassplay::Event {
    class BassplayEvent {
    public:
        explicit BassplayEvent() = default;
        virtual BassplayEventType GetType() { return defaultEvent; }
    };
}



#endif //BASSPLAY_2_BASSPLAYEVENT_H
