//
// Created by aleksander on 30.11.24.
//

#include "JsonPlaylistTransformer.hpp"

namespace Bassplay::Play::Transformer {

    json JsonPlaylistTransformer::TransformToJson(BassplayPlaylist *playlist) {
        json j;
        j["name"] = playlist->GetName();
        j["songs"] = json::array();
        for (auto &song : playlist->GetCollection()->GetSongs()) {
            j["songs"].push_back(JsonSongTransformer::TransformToJson(song));
        }
        return j;
    }

    BassplayPlaylist *JsonPlaylistTransformer::TransformFromJson(std::string &json) {
        auto j = json::parse(json);
        std::string name = j["name"];
        auto playlist = new BassplayPlaylist(name);
        for (auto &song : j["songs"]) {
            std::string songStr = song.dump();
            playlist->AddSong(JsonSongTransformer::TransformFromJson(songStr));
        }
        return playlist;
    }
}