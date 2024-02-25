//
// Created by aleksander on 25.02.24.
//

#ifndef BASSPLAY_2_GUITHREADPAUSELISTENER_H
#define BASSPLAY_2_GUITHREADPAUSELISTENER_H

#include "../event/IBassplayEventHandler.h"
#include "../event/BassplayEvent.h"
#include "../event/BassplayPlaybackEvent.h"
#include <wx/wx.h>

namespace Bassplay::Listener {
    class GuiThreadPauseListener: public Event::IBassplayEventHandler {
    public:
        explicit GuiThreadPauseListener(wxThread* thread): m_guiUpdateThread(thread)  {}
        void Handle(Event::BassplayEvent &event) override;
    private:
        wxThread* m_guiUpdateThread = nullptr;
    };
}

#endif //BASSPLAY_2_GUITHREADPAUSELISTENER_H
