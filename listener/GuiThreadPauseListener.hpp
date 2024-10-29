//
// Created by aleksander on 25.02.24.
//

#ifndef BASSPLAY_2_GUITHREADPAUSELISTENER_HPP
#define BASSPLAY_2_GUITHREADPAUSELISTENER_HPP

#include "../event/IBassplayEventHandler.hpp"
#include "../event/BassplayEvent.hpp"
#include "../event/BassplayPlaybackEvent.hpp"
#include "../ui/PlayerFrame.hpp"
#include <wx/wx.h>

namespace Bassplay::Listener {
    class GuiThreadPauseListener : public Event::IBassplayEventHandler {
    public:
        explicit GuiThreadPauseListener(wxThread *thread, Ui::PlayerFrame *playerFrame) : m_guiUpdateThread(thread),
                                                                                          m_playerFrame(playerFrame) {}

        void Handle(Event::BassplayEvent &event) override;

    private:
        wxThread *m_guiUpdateThread = nullptr;
        Ui::PlayerFrame *m_playerFrame = nullptr;
    };
}

#endif //BASSPLAY_2_GUITHREADPAUSELISTENER_HPP
