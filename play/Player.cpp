//
// Created by aleksander on 30.05.22.
//

#include "Player.h"

namespace Bassplay::Play {
    void Player::LoadSong(std::string* path) {
        HMUSIC hmusic = BASS_MusicLoad(false, path->c_str(), 0, 0, BASS_MUSIC_PRESCAN, 0);
        SongBeingPlayed = new Song(hmusic);
    }
    void Player::PlaySong(std::string *path) {
        if (SongBeingPlayed != nullptr) {
            BASS_ChannelPlay(SongBeingPlayed->GetMusicHandle(), replay);
        }
    }
} // Play