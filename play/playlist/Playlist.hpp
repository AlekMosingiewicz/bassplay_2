//
// Created by aleksander on 30.11.24.
//

#ifndef BASSPLAY_2_PLAYLIST_HPP
#define BASSPLAY_2_PLAYLIST_HPP

#include <string>
#include "../collection/SongCollection.hpp"

namespace Bassplay::Play {

    using Bassplay::Play::Collection::SongCollection;

    class Playlist {
    public:
        explicit Playlist(std::string &name) : m_name(name), m_songs(new SongCollection()) {}

        explicit Playlist(const char *name): m_name(name), m_songs(new SongCollection()) {}

        explicit Playlist(std::string &name, SongCollection *collection) : m_name(name), m_songs(collection) {}

        void SetCollection(SongCollection *collection) { m_songs = collection; }

        [[nodiscard]] SongCollection *GetCollection() const { return m_songs; }

        [[nodiscard]] std::string GetName() const { return m_name; }

        void AddSong(Song *song) { m_songs->AddSong(song); }

        void RemoveSong(const std::string &name) { m_songs->RemoveSong(name); }

        void RemoveAllSongs() { m_songs->RemoveAllSongs(); }

    private:
        std::string m_name;
        SongCollection *m_songs;
    };

}


#endif //BASSPLAY_2_PLAYLIST_HPP
