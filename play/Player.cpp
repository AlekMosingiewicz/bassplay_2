//
// Created by aleksander on 30.05.22.
//

#include "Player.h"

namespace Bassplay::Play {
    void Player::LoadSong(std::string *path) {
        HMUSIC hmusic = BASS_MusicLoad(false, path->c_str(), 0, 0, BASS_MUSIC_PRESCAN, 0);
        if (hmusic != 0) {
            songBeingPlayed = new Song(hmusic);
        } else {
            throw BassplayException(BASS_ErrorGetCode());
        }
    }

    void Player::PlaySong() {
        state = player_state_playing;
        PlayCurrentSong();
    }

    void Player::PauseSong() {
        if (songBeingPlayed != nullptr) {
            BASS_ChannelPause(songBeingPlayed->GetMusicHandle());
            state = player_state_paused;
        }
    }

    void Player::StopSong() {
        if (songBeingPlayed != nullptr) {
            BASS_ChannelStop(songBeingPlayed->GetMusicHandle());
            state = player_state_stopped;
        }
    }

    void Player::PlayCurrentSong() {
        if (songBeingPlayed != nullptr) {
            BASS_ChannelPlay(songBeingPlayed->GetMusicHandle(), replay);
        }
    }
} // Play