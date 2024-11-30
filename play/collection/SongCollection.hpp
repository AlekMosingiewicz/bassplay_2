//
// Created by aleksander on 29.08.22.
//

#ifndef BASSPLAY_2_SONGCOLLECTION_HPP
#define BASSPLAY_2_SONGCOLLECTION_HPP

#include "../serializer/ISerializable.hpp"
#include "../Song.hpp"
#include <list>
#include <iterator>
#include <map>


namespace Bassplay::Play::Collection {

    class SongCollection {
    protected:
        std::map<std::string, Song*> m_songsByName;
        std::list<Song*> m_songs;
        int m_limit = 0;
    public:
        SongCollection() = default;
        ~SongCollection() {
            for (auto &song : m_songsByName) {
                delete song.second;
            }
            RemoveAllSongs();
        }
        [[nodiscard]] std::list<Song*> GetSongs() const { return m_songs; };
        void AddSong(Song* t_song);
        void RemoveSong(const std::string &name);
        void RemoveAllSongs();
        void SetLimit(int p_limit) { m_limit = p_limit; }
    };

} // Bassplay

#endif //BASSPLAY_2_SONGCOLLECTION_HPP
