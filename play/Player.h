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
        explicit Player(bool t_doreplay = false) : replay(t_doreplay), m_songBeingPlayed(nullptr) {}
        explicit Player(Song* t_song, bool t_doreplay = false) : m_songBeingPlayed(t_song), replay(t_doreplay) {}
        ~Player() { delete m_songBeingPlayed; }
        void LoadSong(std::string& path);
        void PlaySong();
        void PauseSong();
        void StopSong();
        [[nodiscard]] int GetState() const { return state; }
        [[nodiscard]] bool HasSong() const { return m_songBeingPlayed != nullptr; }
        [[nodiscard]] Song* GetSong() const { return m_songBeingPlayed; }
        std::string GetCurrentPlaybackTime();
        double GetPlaybackTimeInSeconds();
        void SetReplay(bool t_doReplay) { replay = t_doReplay; }
        void JumpToPosition(double position);
        void CALLBACK OnPlaybackEnd(HSYNC hmusic, DWORD channel, DWORD data, void *user) {  state = player_state_stopped; };
        [[nodiscard]] std::string GetCurrentDirectory() const { return m_currentDirectory; }
    };
} // Play

#endif //BASSPLAY_2_PLAYER_H
