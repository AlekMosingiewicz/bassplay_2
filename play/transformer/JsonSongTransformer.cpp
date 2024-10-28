//
// Created by aleksander on 28.10.24.
//

#include "JsonSongTransformer.hpp"

namespace Bassplay::Play::Transformer {

        using json = nlohmann::json;

        std::string JsonSongTransformer::TransformToJson(Song *song) {
            json j;
            j["filename"] = song->GetFilename();
            j["title"] = song->GetName();
            j["path"] = song->GetPath();
            return j.dump();
        }

        Song* JsonSongTransformer::TransformFromJson(std::string &json) {
            auto j = json::parse(json);
            auto *song = new Song();
            song->SetFilename(j["filename"].dump().c_str());
            song->SetName(j["title"].dump().c_str());
            song->SetPath(j["path"].dump().c_str());
            return song;
        }
}