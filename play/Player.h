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

    class Player {
    private:
        //fields
        Song* songBeingPlayed = nullptr;
        bool  replay;
        int state = player_state_stopped;
        //methods
        void PlayCurrentSong();
    public:
        Player(bool doreplay = false) : replay(doreplay), songBeingPlayed(nullptr) {}
        Player(Song* song, bool doreplay = false) : songBeingPlayed(song), replay(doreplay) {}
        ~Player() { if (songBeingPlayed != nullptr) { delete songBeingPlayed; } }
        void LoadSong(std::string* path);
        void PlaySong();
        void PauseSong();
        void StopSong();
        int GetState() { return state; }
        bool HasSong() { return songBeingPlayed != nullptr; }
        Song* GetSong() { return songBeingPlayed; }
        void SetReplay(bool doReplay) { replay = doReplay; }
    };
} // Play

#endif //BASSPLAY_2_PLAYER_H
