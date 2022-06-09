//
// Created by aleksander on 30.05.22.
//

#ifndef BASSPLAY_2_PLAYER_H
#define BASSPLAY_2_PLAYER_H

#include "Song.h"
#include <wx/string.h>
#include <wx/file.h>

namespace Bassplay::Play {

    class Player {
    private:
        Song* SongBeingPlayed;
        bool  replay;
    public:
        Player(Song* song, bool doreplay = false) : SongBeingPlayed(song), replay(doreplay) {}
        void LoadSong(std::string* path);
        void PlaySong(std::string* path = nullptr);
        void StopSong() { BASS_ChannelStop(SongBeingPlayed->GetMusicHandle()); }
        void PauseSong() { BASS_ChannelPause(SongBeingPlayed->GetMusicHandle()); }
        void SetReplay(bool doReplay) { replay = doReplay; }
    };
} // Play

#endif //BASSPLAY_2_PLAYER_H
