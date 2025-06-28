//
// Created by aleksander on 28.06.25.
//

#include "BulkPlaylistsPersister.hpp"

namespace Bassplay::Play::Persistence {
    void BulkPlaylistsPersister::persist(const std::list<Playlist*>& playlists) {
        nlohmann::json j;
        j["playlists"] = nlohmann::json::array();

        for (auto playlist: playlists) {
            j["playlists"].push_back(Bassplay::Play::Transformer::JsonPlaylistTransformer::TransformToJson(playlist));
        }
        m_ostream->write(j.dump().c_str(),static_cast<std::streamsize>(j.dump().size()));
    }
}