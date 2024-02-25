//
// Created by aleksander on 25.02.24.
//

#ifndef BASSPLAY_2_IBASSPLAYEVENTHANDLER_H
#define BASSPLAY_2_IBASSPLAYEVENTHANDLER_H

#include "BassplayEvent.h"

namespace Bassplay::Event {
    class IBassplayEventHandler {
    public:
        virtual void Handle(BassplayEvent& event) {};
    };
}
#endif //BASSPLAY_2_IBASSPLAYEVENTHANDLER_H
