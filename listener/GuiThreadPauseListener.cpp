//
// Created by aleksander on 25.02.24.
//

#include "GuiThreadPauseListener.h"

namespace Bassplay::Listener {
    void GuiThreadPauseListener::Handle(Event::BassplayEvent &event) {
        auto& playbackEvent =
                dynamic_cast<Bassplay::Event::BassplayPlaybackEvent&>(event);
        if (playbackEvent.GetPlaybackEventType() == Event::playbackStopped) {
            m_guiUpdateThread->Pause();
        } else if (playbackEvent.GetPlaybackEventType() == Event::playbackStarted) {
            m_guiUpdateThread->Resume();
        } else if (playbackEvent.GetPlaybackEventType() == Event::playbackEnded) {
            m_playerFrame->StopAndReset();
        }
    }
}