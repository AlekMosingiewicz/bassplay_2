//
// Created by aleksander on 25.02.24.
//

#ifndef BASSPLAY_2_BASSPLAYEVENT_HPP
#define BASSPLAY_2_BASSPLAYEVENT_HPP

#include "BassplayEventType.hpp"

namespace Bassplay::Event {
    class BassplayEvent {
    public:
        explicit BassplayEvent() = default;
        virtual BassplayEventType GetType() { return defaultEvent; }
    };
}



#endif //BASSPLAY_2_BASSPLAYEVENT_HPP
