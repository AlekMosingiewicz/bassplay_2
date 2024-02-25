//
// Created by aleksander on 25.02.24.
//

#include "GuiThreadPauseListener.h"

namespace Bassplay::Listener {
    void GuiThreadPauseListener::Handle(Event::BassplayPlaybackEvent &event) {
        auto& playbackEvent =
                dynamic_cast<Bassplay::Event::BassplayPlaybackEvent&>(event);
        if (playbackEvent.GetPlaybackEventType() == Event::playbackStopped) {
            m_guiUpdateThread->Pause();
        } else {
            m_guiUpdateThread->Resume();
        }
    }
}