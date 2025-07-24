//
// Created by aleksander on 30.11.24.
//

#ifndef BASSPLAY_2_BASSPLAYPLAYLIST_HPP
#define BASSPLAY_2_BASSPLAYPLAYLIST_HPP

#include <string>
#include "../collection/SongCollection.hpp"

namespace Bassplay::Play::Playlist {

    using Bassplay::Play::Collection::SongCollection;

    class BassplayPlaylist {
    public:
        explicit BassplayPlaylist(std::string &name) : m_name(name), m_songs(new SongCollection()) {}

        explicit BassplayPlaylist(const char *name): m_name(name), m_songs(new SongCollection()) {}

        explicit BassplayPlaylist(std::string &name, SongCollection *collection) : m_name(name), m_songs(collection) {}

        void SetCollection(SongCollection *collection) { m_songs = collection; }

        [[nodiscard]] SongCollection *GetCollection() const { return m_songs; }

        [[nodiscard]] std::string GetName() const { return m_name; }

        void AddSong(Song *song) { m_songs->AddSong(song); }

        void RemoveSong(const std::string &name) { m_songs->RemoveSong(name); }

        void RemoveAllSongs() { m_songs->RemoveAllSongs(); }

        int GetCurrentSongIndex(int index) {
            if (index < 0 || index >= m_songs->GetSize()) {
                return -1; // Invalid index
            }
            m_currentSongIndex = index;
            return m_currentSongIndex;
        }

        void IncrementCurrentSongIndex() {
            m_currentSongIndex++;
            if (m_currentSongIndex >= m_songs->GetSize()) {
                m_currentSongIndex = 0; // Loop back to the start
            }
        }

        void DecrementCurrentSongIndex() {
            m_currentSongIndex--;
            if (m_currentSongIndex < 0) {
                m_currentSongIndex = m_songs->GetSize() - 1; // Loop to the end
            }
        }

        void SetCurrentSongIndex(int index) {
            if (index >= 0 && index < m_songs->GetSize()) {
                m_currentSongIndex = index;
            } else {
                m_currentSongIndex = 0; // Reset to the first song if index is invalid
            }
        }

        void ResetCurrentSongIndex() {
            m_currentSongIndex = 0; // Reset to the first song
        }

        [[nodiscard]] bool IsEmpty() const { return m_songs->IsEmpty(); }

        [[nodiscard]] Song *GetCurrentSong() const {
            return m_songs->GetByIndex(m_currentSongIndex);
        }

        [[nodiscard]] int GetCurrentSongIndex() const { return m_currentSongIndex; }

    private:
        std::string m_name;
        SongCollection *m_songs;
        int m_currentSongIndex = 0;
    };

}


#endif //BASSPLAY_2_BASSPLAYPLAYLIST_HPP
