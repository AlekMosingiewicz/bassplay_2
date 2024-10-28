//
// Created by aleksander on 30.05.22.
//

#ifndef BASSPLAY_2_PLAYER_H
#define BASSPLAY_2_PLAYER_H

#include "Song.h"
#include "collection/SongCollection.h"
#include "../event/BassplayEvent.h"
#include "../event/BassplayEventDispatcher.h"
#include "../event/BassplayPlaybackEvent.h"
#include "history/history.hpp"

namespace Bassplay::Play {

    using namespace Bassplay::Play::Collection;
    using namespace Bassplay::Event;
    using Bassplay::Play::History::PlaybackHistory;

    enum player_state {
        player_state_stopped,
        player_state_playing,
        player_state_paused
    };

    void CALLBACK on_playback_end(HSYNC hmusic, DWORD channel, DWORD data, void *user);

    class Player {
    private:
        //fields
        Song* m_songBeingPlayed = nullptr;
        bool  replay;
        int   state = player_state_stopped;
        float mVolume = 1;
        std::string m_currentDirectory;
        SongCollection* m_playlist = nullptr;
        SongCollection* m_history_collection = nullptr;
        PlaybackHistory *m_history = nullptr;

        //methods
        void PlayCurrentSong();
        void SetCurrentDirectory(std::string &path);
        void BassUpdateVolume() const;
        static void BroadcastPlaybackEvent(Bassplay::Event::PlaybackEventType eventType);
    public:
        explicit Player(bool t_doreplay = false) : replay(t_doreplay), m_songBeingPlayed(nullptr), m_playlist(new Collection::SongCollection()) {
            m_history_collection = new SongCollection();
            m_history_collection->SetLimit(5);
        };
        explicit Player(Song* t_song, bool t_doreplay = false) : m_songBeingPlayed(t_song), replay(t_doreplay) {}
        ~Player();
        void LoadSong(std::string& path);
        void PlaySong();
        void PauseSong();
        void StopSong();
        void SetVolume(float volume) { mVolume = volume; BassUpdateVolume(); }
        [[nodiscard]] int GetState() const { return state; }
        [[nodiscard]] bool HasSong() const { return m_songBeingPlayed != nullptr; }
        [[nodiscard]] Song* GetSong() const { return m_songBeingPlayed; }
        [[nodiscard]] SongCollection* GetPlaylist() { return m_playlist; };
        [[nodiscard]] SongCollection* GetHistoryCollection() { return m_history_collection; };
        void SetPlaylist(SongCollection* p_songCollection) {
            if (m_playlist != nullptr) delete m_playlist;
            m_playlist = p_songCollection;
        }
        void SetHistory(SongCollection* p_history) {
            if (m_history_collection != nullptr) delete m_history_collection;
            m_history_collection = p_history;
        }
        std::string GetCurrentPlaybackTime();
        double GetPlaybackTimeInSeconds();
        float GetVolume() { return mVolume; }
        void SetReplay(bool t_doReplay) { replay = t_doReplay; }
        void SetPlaybackHistory(PlaybackHistory *history) { m_history = history; }
        PlaybackHistory* GetPlaybackHistory() { return m_history; }
        void JumpToPosition(double position);
        void CALLBACK OnPlaybackEnd(HSYNC hmusic, DWORD channel, DWORD data, void *user) {  state = player_state_stopped; };
        [[nodiscard]] std::string GetCurrentDirectory() const { return m_currentDirectory; }
    };
} // Play

#endif //BASSPLAY_2_PLAYER_H
