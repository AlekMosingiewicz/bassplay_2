//
// Created by aleksander on 30.05.22.
//

#ifndef BASSPLAY_2_PLAYER_H
#define BASSPLAY_2_PLAYER_H

#include "Song.h"


namespace Bassplay::Play {

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
        int state = player_state_stopped;
        std::string m_currentDirectory;
        //methods
        void PlayCurrentSong();
        void SetCurrentDirectory(std::string &path);
    public:
        Player(bool doreplay = false) : replay(doreplay), m_songBeingPlayed(nullptr) {}
        Player(Song* song, bool doreplay = false) : m_songBeingPlayed(song), replay(doreplay) {}
        ~Player() { if (m_songBeingPlayed != nullptr) { delete m_songBeingPlayed; } }
        void LoadSong(std::string& path);
        void PlaySong();
        void PauseSong();
        void StopSong();
        int GetState() { return state; }
        bool HasSong() { return m_songBeingPlayed != nullptr; }
        Song* GetSong() { return m_songBeingPlayed; }
        std::string GetCurrentPlaybackTime();
        void SetReplay(bool doReplay) { replay = doReplay; }
        void CALLBACK OnPlaybackEnd(HSYNC hmusic, DWORD channel, DWORD data, void *user) {  state = player_state_stopped; };
        std::string GetCurrentDirectory() { return m_currentDirectory; }
    };
} // Play

#endif //BASSPLAY_2_PLAYER_H
