//
// Created by aleksander on 30.05.22.
//

#ifndef BASSPLAY_2_PLAYER_H
#define BASSPLAY_2_PLAYER_H

#include "Song.h"


namespace Bassplay::Play {

    class Player {
    private:
        //fields
        Song* songBeingPlayed = nullptr;
        bool  replay;
        //methods
        void PlayCurrentSong();
    public:
        Player(bool doreplay = false) : replay(doreplay), songBeingPlayed(nullptr) {}
        Player(Song* song, bool doreplay = false) : songBeingPlayed(song), replay(doreplay) {}
        ~Player() { if (songBeingPlayed != nullptr) { delete songBeingPlayed; } }
        void LoadSong(std::string* path);
        void PlaySong();
        void StopSong() { if (songBeingPlayed != nullptr) BASS_ChannelStop(songBeingPlayed->GetMusicHandle()); }
        void PauseSong() { if (songBeingPlayed != nullptr) BASS_ChannelPause(songBeingPlayed->GetMusicHandle()); }
        bool HasSong() { return songBeingPlayed != nullptr; }
        Song* GetSong() { return songBeingPlayed; }
        void SetReplay(bool doReplay) { replay = doReplay; }
    };
} // Play

#endif //BASSPLAY_2_PLAYER_H
