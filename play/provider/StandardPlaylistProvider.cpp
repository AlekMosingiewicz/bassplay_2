//
// Created by aleksander on 29.06.25.
//

#include "StandardPlaylistProvider.hpp"

namespace Bassplay::Play::Provider {

    std::map<std::string, BassplayPlaylist *> *StandardPlaylistProvider::GetPlaylists() {
        auto *playlists = new std::map<std::string, BassplayPlaylist *>();

        if (m_inputStream == nullptr) {
            return playlists; // Return empty map if input stream is null
        }

        if (m_inputStream->is_open()) {
            std::string jsonContent((std::istreambuf_iterator<char>(*m_inputStream)),
                                    std::istreambuf_iterator<char>());
            if (jsonContent.empty()) {
                return playlists; // Return empty map if JSON content is empty
            }
            auto j = nlohmann::json::parse(jsonContent);

            for (const auto &item: j["playlists"]) {
                std::string playlistName = item["name"];
                std::string playlistJsonString = std::string(item.dump());
                auto playlist = JsonPlaylistTransformer::TransformFromJson(playlistJsonString);
                playlists->insert({playlistName, playlist});
            }
        } else {
            throw std::runtime_error("Input stream is not open.");
        }
        return playlists;
    }
} // Bassplay