//
// Created by aleksander on 25.02.24.
//

#ifndef BASSPLAY_2_IBASSPLAYEVENTHANDLER_HPP
#define BASSPLAY_2_IBASSPLAYEVENTHANDLER_HPP

#include "BassplayEvent.hpp"

namespace Bassplay::Event {
    class IBassplayEventHandler {
    public:
        virtual void Handle(BassplayEvent& event) {};
    };
}
#endif //BASSPLAY_2_IBASSPLAYEVENTHANDLER_HPP
