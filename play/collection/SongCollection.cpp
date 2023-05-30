//
// Created by aleksander on 29.08.22.
//

#include "SongCollection.h"

namespace Bassplay::Play::Collection {
    std::list<Song*> SongCollection::GetSongs() const {
        std::list<Song*> songs;

        for (const auto &song : m_songs) {
            songs.push_back(song.second);
        }
        return songs;
    }

    void SongCollection::AddSong(Bassplay::Play::Song *t_song) {
        std::string name = t_song->GetFilename();
        if (name.empty()) {
            name = std::string(t_song->GetName());
        }
        m_songs[name] = t_song;
    }

    void SongCollection::RemoveSong(const std::string &name) {
        for (auto it = m_songs.begin(); it != m_songs.end(); it++) {
            if (it->first == name) {
                m_songs.erase(it);
            }
        }
    }

    void SongCollection::RemoveAllSongs() {
        m_songs.clear();
    }
} // Bassplay