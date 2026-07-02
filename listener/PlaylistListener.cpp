//
// Created by aleksander on 23.10.2025.
//

#include "PlaylistListener.hpp"


namespace Bassplay::Listener {
    using namespace Bassplay;

    void PlaylistListener::Handle(Event::BassplayEvent &event) {
        try {
            auto& playbackEvent = 
                dynamic_cast<Event::BassplayPlaybackEvent&>(event);
            
            HandlePlaybackEvent(playbackEvent);
            return;
        } catch {}

        try {
            auto& guiEvent = 
                    dynamic_cast<Event::BassplayGuiEvent&>(event);                    
            HandleGuiEvent(guiEvent);
            return;
        } catch {}                

    }

    void PlaylistListener::HandlePlaybackEvent(Event::BassplayPlaybackEvent &event) {
        if (m_playlistFrame == nullptr || !m_playlistFrame->IsShown() || m_player->GetPlaylist() == nullptr) {
            return;
        }
        if (event.GetPlaybackEventType() == Event::PlaybackEventType::playbackStarted) {
            int index = m_player->GetPlaylist()->GetCurrentSongIndex();
            m_playlistFrame->SetCurrentSongIndex(index);
        }
    }

    void PlaylistListener::HandleGuiEvent(Event::BassplayGuiEvent &event) {
        if (m_playlistFrame == nullptr) {
            return;
        }
        if (event.GetGuiEventType() != Event::GuiEventType::playlistWindowClosed) {
            return;
        }
        m_playlistFrame = nullptr;
    }
}