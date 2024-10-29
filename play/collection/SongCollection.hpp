//
// Created by aleksander on 29.08.22.
//

#ifndef BASSPLAY_2_SONGCOLLECTION_HPP
#define BASSPLAY_2_SONGCOLLECTION_HPP

#include "../serializer/ISerializable.h"
#include "../Song.hpp"
#include <list>
#include <unordered_map>
#include <iterator>


namespace Bassplay::Play::Collection {

    class SongCollection {
    protected:
        std::unordered_map<std::string, Song*> m_songs;
        int m_limit = 0;
    public:
        SongCollection() = default;
        ~SongCollection() {
            for (auto &song : m_songs) {
                delete song.second;
            }
            RemoveAllSongs();
        }
        [[nodiscard]] std::list<Song*> GetSongs() const;
        void AddSong(Song* t_song);
        void RemoveSong(const std::string &name);
        void RemoveAllSongs();
        void SetLimit(int p_limit) { m_limit = p_limit; }
    };

} // Bassplay

#endif //BASSPLAY_2_SONGCOLLECTION_HPP
