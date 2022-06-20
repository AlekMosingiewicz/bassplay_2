//
// Created by aleksander on 30.05.22.
//

#include "Player.h"

namespace Bassplay::Play {
    void Player::LoadSong(std::string &path) {
        if (m_songBeingPlayed != nullptr) {
            m_songBeingPlayed->UnloadSong();
        }
        HMUSIC hmusic = BASS_MusicLoad(false, path.c_str(), 0, 0, BASS_MUSIC_PRESCAN, 0);
        if (hmusic != 0) {
            SetCurrentDirectory(path);
            m_songBeingPlayed = new Song(hmusic);
        } else {
            throw BassplayException(BASS_ErrorGetCode());
        }
    }

    void Player::PlaySong() {
        state = player_state_playing;
        PlayCurrentSong();
    }

    void Player::PauseSong() {
        if (m_songBeingPlayed != nullptr) {
            BASS_ChannelPause(m_songBeingPlayed->GetMusicHandle());
            state = player_state_paused;
        }
    }

    void Player::StopSong() {
        if (m_songBeingPlayed != nullptr) {
            BASS_ChannelStop(m_songBeingPlayed->GetMusicHandle());
            state = player_state_stopped;
        }
    }

    void Player::PlayCurrentSong() {
        if (m_songBeingPlayed != nullptr) {
            BASS_ChannelPlay(m_songBeingPlayed->GetMusicHandle(), replay);
        }
    }

    std::string Player::GetCurrentPlaybackTime() {
        if (m_songBeingPlayed != nullptr) {
            double rawPlaybackTime = m_songBeingPlayed->GetCurrentPlaybackTime();
            double totalPlaybackTime = m_songBeingPlayed->Length();
            int cmins = (int)rawPlaybackTime / 60;
            int csecs = (int)rawPlaybackTime % 60;
            int tmins = (int)totalPlaybackTime / 60;
            int tsecs = (int)totalPlaybackTime % 60;
            char temp[12];
            sprintf(temp, "%02d:%02d/%02d:%02d", cmins, csecs, tmins, tsecs);
            return {temp};
        }
        return {"No song loaded"};
    }

    void Player::SetCurrentDirectory(std::string &path) {
        size_t last_slash_pos = path.find_last_of('/');
        std::string dir = path.substr(0, last_slash_pos);
        m_currentDirectory = std::string (dir);
    }
} // Play