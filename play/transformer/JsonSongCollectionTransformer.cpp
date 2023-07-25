//
// Created by aleksander on 11.06.23.
//

#include "JsonSongCollectionTransformer.h"

namespace Bassplay::Play::Transformer {
    Bassplay::Play::Collection::SongCollection* JsonSongCollectionTransformer::Transform(const char *src) {
        auto *collection = new Bassplay::Play::Collection::SongCollection;
        std::string jsonString(src);
        m_jsonParser->Parse(jsonString);
        std::vector<std::unordered_map<std::string,std::string >> data = m_jsonParser->GetData();

        for (const auto &datum: data) {
            collection->AddSong(CreateSong(datum));
        }

        return collection;
    }

    Bassplay::Play::Song* JsonSongCollectionTransformer::CreateSong(std::unordered_map<std::string, std::string> data) {
        Song* song = new Song();
        song->SetFilename(data["filename"]);
        song->SetName(data["title"]);
        song->SetPath(data["path"]);
        return song;
    }
} // Bassplay