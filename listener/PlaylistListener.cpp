//
// Created by aleksander on 23.10.2025.
//

#include "PlaylistListener.hpp"


namespace Bassplay::Listener {
    using namespace Bassplay;

    void PlaylistListener::Handle(Event::BassplayEvent &event) {
        auto& playbackEvent =
                dynamic_cast<Event::BassplayPlaybackEvent&>(event);

        if (m_playlistFrame != nullptr && !m_playlistFrame->IsVisible()) {
            return;
        }

        if (m_player->GetPlaylist() == nullptr || m_playlistFrame == nullptr) {
            return;
        }
        if (playbackEvent.GetPlaybackEventType() == Event::PlaybackEventType::playbackStarted) {
            int index = m_player->GetPlaylist()->GetCurrentSongIndex();
            m_playlistFrame->SetCurrentSongIndex(index);
        }
    }
}