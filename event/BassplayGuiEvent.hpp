
#ifndef BASSPLAY_2_BASSPLAYGUIEVENT_HPP
#define BASSPLAY_2_BASSPLAYGUIEVENT_HPP

#include "BassplayEventType.hpp"
#include "BassplayEvent.hpp"

namespace Bassplay::Event {

    enum GuiEventType {
        playlistWindowClosed
    };

    class BassplayGuiEvent : public BassplayEvent {
    public:
        explicit BassplayGuiEvent(GuiEventType guiEventType) :
                                                                     m_guiEventType(guiEventType) {}

       GuiEventType GetGuiEventType() { return m_guiEventType; }
       BassplayEventType GetType() { return guiEvent; }
    private:
        GuiEventType m_guiEventType;
    };

}

#endif //BASSPLAY_2_BASSPLAYGUIEVENT_HPP