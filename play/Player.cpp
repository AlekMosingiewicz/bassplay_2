//
// Created by aleksander on 30.05.22.
//

#include "Player.h"

namespace Bassplay::Play {
    void CALLBACK on_playback_end(HSYNC hmusic, DWORD channel, DWORD data, void *user) {
        auto player = static_cast<Player *>(user);
        player->StopSong();
    }

    void Player::LoadSong(std::string &path) {
        if (m_songBeingPlayed != nullptr) {
            m_songBeingPlayed->UnloadSong();
        }
        try {
            m_songBeingPlayed = new Song(path);
            SetCurrentDirectory(path);
            if (m_history != nullptr) {
                m_history->AddSong(m_songBeingPlayed);
            }
        } catch (BassplayException &bassplayException) {
            throw bassplayException;
        }
        BassUpdateVolume();
    }

    void Player::PlaySong() {
        state = player_state_playing;
        PlayCurrentSong();
        auto event = Bassplay::Event::BassplayPlaybackEvent(
                Bassplay::Event::PlaybackEventType::playbackStarted);
        Bassplay::Event::BassplayEventDispatcher::Instance().BroadcastEvent<Bassplay::Event::BassplayPlaybackEvent>(event);
    }

    void Player::PauseSong() {
        if (m_songBeingPlayed != nullptr) {
            BASS_ChannelPause(m_songBeingPlayed->GetMusicHandle());
            state = player_state_paused;
            auto event = Bassplay::Event::BassplayPlaybackEvent(
                            Bassplay::Event::PlaybackEventType::playbackStopped);

            Bassplay::Event::BassplayEventDispatcher::Instance().BroadcastEvent<Bassplay::Event::BassplayPlaybackEvent>(event);
        }
    }

    void Player::StopSong() {
        if (m_songBeingPlayed != nullptr) {
            BASS_ChannelStop(m_songBeingPlayed->GetMusicHandle());
            state = player_state_stopped;
            m_songBeingPlayed->Rewind();

            auto event = Bassplay::Event::BassplayPlaybackEvent(
                    Bassplay::Event::PlaybackEventType::playbackStopped);

            Bassplay::Event::BassplayEventDispatcher::Instance().BroadcastEvent<Bassplay::Event::BassplayPlaybackEvent>(event);
        }
    }

    void Player::PlayCurrentSong() {
        if (m_songBeingPlayed != nullptr) {
            BASS_ChannelPlay(m_songBeingPlayed->GetMusicHandle(), replay);
            BASS_ChannelSetSync(m_songBeingPlayed->GetMusicHandle(), BASS_SYNC_END, 0, &on_playback_end, this);
        }
    }

    std::string Player::GetCurrentPlaybackTime() {
        if (m_songBeingPlayed != nullptr) {
            double rawPlaybackTime = m_songBeingPlayed->GetCurrentPlaybackTime();
            double totalPlaybackTime = m_songBeingPlayed->GetLength();
            int cmins = (int) rawPlaybackTime / 60;
            int csecs = (int) rawPlaybackTime % 60;
            int tmins = (int) totalPlaybackTime / 60;
            int tsecs = (int) totalPlaybackTime % 60;
            char temp[12];
            sprintf(temp, "%02d:%02d/%02d:%02d", cmins, csecs, tmins, tsecs);
            return {temp};
        }
        return {"No song loaded"};
    }

    double Player::GetPlaybackTimeInSeconds() {
        if (m_songBeingPlayed != nullptr) {
            return m_songBeingPlayed->GetCurrentPlaybackTime();
        }
        return 0;
    }

    void Player::SetCurrentDirectory(std::string &path) {
        size_t last_slash_pos = path.find_last_of('/');
        std::string dir = path.substr(0, last_slash_pos);
        m_currentDirectory = std::string(dir);
    }

    void Player::JumpToPosition(double position) {
        if (m_songBeingPlayed != nullptr) {
            BASS_ChannelSetPosition(
                    m_songBeingPlayed->GetMusicHandle(),
                    BASS_ChannelSeconds2Bytes(m_songBeingPlayed->GetMusicHandle(), position),
                    BASS_POS_BYTE
            );
        }
    }

    void Player::BassUpdateVolume() const {
        if (mVolume > 0 && mVolume < 1) {
            m_songBeingPlayed->SetVolume(mVolume);
        }
    }
} // Play