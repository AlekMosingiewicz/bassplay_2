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
            std::string songJson = element.dump();
            collection->AddSong(JsonSongTransformer::TransformFromJson(songJson));
        }

        if (j.contains("lastSong")) {
            std::string songJson = j["lastSong"].dump();
            history->SetLastSong(JsonSongTransformer::TransformFromJson(songJson));
        }

        history->SetCollection(collection);

        return history;
    }
}