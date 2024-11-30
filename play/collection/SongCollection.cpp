//
// Created by aleksander on 29.08.22.
//

#include "SongCollection.hpp"

namespace Bassplay::Play::Collection {
    void SongCollection::AddSong(Bassplay::Play::Song *t_song) {
        if (m_limit > 0 && m_songsByName.size() + 1 > m_limit) {
            for (auto it = m_songs.begin(); it != m_songs.end(); it++) {
                if (std::next(it) == m_songs.end()) {
                    m_songs.pop_front();
                    m_songsByName.erase((*it)->GetFilename());
                    break;
                }
            }
        }
        std::string name = t_song->GetFilename();
        if (name.empty()) {
            name = std::string(t_song->GetName());
        }
        m_songsByName[name] = t_song;
        m_songs.insert(m_songs.end(), t_song);
    }

    void SongCollection::RemoveSong(const std::string &name) {
        m_songsByName.erase(name);
        for (auto it = m_songs.begin(); it != m_songs.end(); it++) {
            if ((*it)->GetFilename() == name) {
                m_songs.erase(it);
                break;
            }
        }
    }

    void SongCollection::RemoveAllSongs() {
        m_songsByName.clear();
    }
} // Bassplay