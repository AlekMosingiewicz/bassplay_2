//
// Created by aleksander on 25.02.24.
//

#include "GuiThreadPauseListener.hpp"

namespace Bassplay::Listener {
    void GuiThreadPauseListener::Handle(Event::BassplayEvent &event) {
        auto& playbackEvent =
                dynamic_cast<Bassplay::Event::BassplayPlaybackEvent&>(event);
        if (playbackEvent.GetPlaybackEventType() == Event::playbackStopped && m_guiUpdateThread->IsRunning()) {
            m_guiUpdateThread->Pause();
        } else if (playbackEvent.GetPlaybackEventType() == Event::playbackStarted) {
            m_playerFrame->ResetPositionSlider();
            m_playerFrame->UpdateGUI(true);
            m_guiUpdateThread->Resume();
        } else if (playbackEvent.GetPlaybackEventType() == Event::playbackResumed && !m_guiUpdateThread->IsRunning()) {
            m_guiUpdateThread->Resume();
        } else if (playbackEvent.GetPlaybackEventType() == Event::playbackEnded) {
            m_playerFrame->StopAndReset();
        }
    }
}