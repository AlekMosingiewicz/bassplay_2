//
// Created by aleksander on 28.10.24.
//

#include "JsonSongTransformer.hpp"

namespace Bassplay::Play::Transformer {

        json JsonSongTransformer::TransformToJson(Song *song) {
            json j;
            j["filename"] = song->GetFilename();
            j["title"] = song->GetTitle();
            j["path"] = song->GetPath();
            return j;
        }

        Song* JsonSongTransformer::TransformFromJson(std::string &json) {
            auto j = json::parse(json);
            auto *song = new Song();

            auto filename = j["filename"].dump();
            auto title = j["title"].dump();
            auto path = j["path"].dump();

            song->SetFilename(SanitizeString(filename).c_str());
            song->SetName(SanitizeString(title).c_str());
            song->SetPath(SanitizeString(path).c_str());
            return song;
        }

        std::string JsonSongTransformer::SanitizeString(std::string &str) {
            if (!str.empty() && str.front() == '\"' && str.back() == '\"') {
                str = str.substr(1, str.size() - 2);
            }
            return str;
        }
}