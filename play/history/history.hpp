//
// Created by aleksander on 28.10.24.
//

#ifndef BASSPLAY_2_HISTORY_HPP
#define BASSPLAY_2_HISTORY_HPP

#include "../collection/SongCollection.hpp"
#include "../../json/json.hpp"
#include "../transformer/JsonSongTransformer.hpp"

namespace Bassplay::Play::History {

    using namespace Bassplay::Play::Collection;
    using Bassplay::Play::Song;
    using Bassplay::Play::Transformer::JsonSongTransformer;

    class PlaybackHistory {
    public:
        PlaybackHistory() = default;
        ~PlaybackHistory() {
            delete m_collection;
            delete m_lastSong;
        }
        void SetCollection(SongCollection *collection) { m_collection = collection; }
        void SetLastSong(Song *lastSong) { m_lastSong = lastSong; }
        [[nodiscard]] SongCollection* GetCollection() const { return m_collection; }
        [[nodiscard]] Song* GetLastSong() const { return m_lastSong; }
        static PlaybackHistory* CreateFromJson(std::string &json);

    private:
        SongCollection *m_collection = nullptr;
        Song *m_lastSong = nullptr;
    };

}
#endif //BASSPLAY_2_HISTORY_HPP
