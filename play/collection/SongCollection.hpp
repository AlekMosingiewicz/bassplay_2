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
#include <memory>


namespace Bassplay::Play::Collection {

    class SongCollection {
    protected:
        std::map<std::string, std::shared_ptr<Song>> m_songsByName;
        std::list<std::shared_ptr<Song>> m_songs;
        int m_limit = 0;
    public:
        SongCollection() = default;
        ~SongCollection() {}
        [[nodiscard]] std::list<std::shared_ptr<Song>> GetSongs() const { return m_songs; };
        void AddSong(std::shared_ptr<Song> t_song);
        void RemoveSong(const std::string &name);
        void RemoveAllSongs();
        void SetLimit(int p_limit) { m_limit = p_limit; }
        std::shared_ptr<Song> GetByIndex(int index);
        [[nodiscard]] int GetSize() const { return m_songs.size(); }
        [[nodiscard]] int GetLimit() const { return m_limit; }
        [[nodiscard]] bool IsEmpty() const { return m_songs.empty(); }
    };

} // Bassplay

#endif //BASSPLAY_2_SONGCOLLECTION_HPP
