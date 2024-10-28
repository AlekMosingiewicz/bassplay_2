//
// Created by aleksander on 28.10.24.
//

#include "PlaybackHistoryPersister.hpp"

namespace Bassplay::Play::Persistence {

        void PlaybackHistoryPersister::persist(const PlaybackHistory *history) {
            json j;
            j["history"] = json::array();
            for (auto &song: history->GetCollection()->GetSongs()) {
                j["history"].push_back(JsonSongTransformer::TransformToJson(song));
            }

            if (history->GetLastSong() != nullptr) {
                j["lastSong"] = JsonSongTransformer::TransformToJson(history->GetLastSong());
            }

            if (history->GetDir() != nullptr) {
                j["dir"] = *history->GetDir();
            }

            m_ostream->write(j.dump().c_str(), j.dump().size());
        }
}