//
// Created by aleksander on 28.10.24.
//

#include "history.hpp"


namespace Bassplay::Play::History {

    using json = nlohmann::json;

    PlaybackHistory* PlaybackHistory::CreateFromJson(std::string &json) {
        auto j = json::parse(json);
        auto *history = new PlaybackHistory();
        auto *collection = new SongCollection;
        for (auto &element: j["history"]) {
            Song *song = new Song();
            song->SetFilename(element["filename"].dump().c_str());
            song->SetName(element["title"].dump().c_str());
            song->SetPath(element["path"].dump().c_str());
            collection->AddSong(song);
        }
        auto *lastSong = new std::string(j["lastSong"].dump());
        history->SetCollection(collection);
        history->SetLastSong(lastSong);

        return history;
    }
}