//
// Created by aleksander on 28.06.25.https://www.youtube.com/watch?v=jQExvvCe5OM
//

#include "BulkPlaylistsPersister.hpp"

namespace Bassplay::Play::Persistence {
    void BulkPlaylistsPersister::persist(const std::list<BassplayPlaylist*>& playlists) {
        nlohmann::json j;
        j["playlists"] = nlohmann::json::array();

        for (auto playlist: playlists) {
            j["playlists"].push_back(Bassplay::Play::Transformer::JsonPlaylistTransformer::TransformToJson(playlist));
        }
        m_ostream->write(j.dump().c_str(),static_cast<std::streamsize>(j.dump().size()));
    }
}