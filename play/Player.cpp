//
// Created by aleksander on 30.05.22.
//

#include "Player.hpp"

namespace Bassplay::Play {
    void CALLBACK on_playback_end(HSYNC hmusic, DWORD channel, DWORD data, void *user) {
        auto player = static_cast<Player *>(user);
        auto event = BassplayPlaybackEvent(
                PlaybackEventType::playbackEnded);
       BassplayEventDispatcher::Instance().BroadcastEvent<BassplayPlaybackEvent>(
                event);
       player->StopSong();
       if (player->GetPlaylist() != nullptr) {
           player->PlayNextSong();
       }
    }

    void Player::LoadSong(std::string &path) {
        if (m_songBeingPlayed != nullptr) {
            BroadcastPlaybackEvent(PlaybackEventType::playbackStopped);
            m_songBeingPlayed->UnloadSong();
            delete m_songBeingPlayed;
            m_songBeingPlayed = nullptr;
        }
        try {
            m_songBeingPlayed = new Song(path);
            SetCurrentDirectory(path);
            if (m_history != nullptr && m_history->GetCollection() != nullptr) {
                m_history->GetCollection()->AddSong(m_songBeingPlayed);
            }
            if (m_history != nullptr) {
                m_history->SetLastSong(m_songBeingPlayed);
                m_history->SetDir(&m_currentDirectory);
            }
        } catch (BassplayException &bassplayException) {
            throw bassplayException;
        }
        BassUpdateVolume();
    }

    void Player::PlaySong() {
        m_state = player_state_playing;
        PlayCurrentSong();
        BroadcastPlaybackEvent(PlaybackEventType::playbackStarted);
    }

    void Player::PauseSong() {
        if (m_songBeingPlayed != nullptr) {
            BroadcastPlaybackEvent(PlaybackEventType::playbackStopped);
            BASS_ChannelPause(m_songBeingPlayed->GetMusicHandle());
            m_state = player_state_paused;
        }
    }

    void Player::PlayFromPlaylist() {
        if (m_playlist != nullptr && m_playlist->GetCollection() != nullptr) {
            auto path = m_playlist->GetCurrentSong()->GetPath();
            LoadSong(path);
            PlayCurrentSong();
        } else {
            //TODO handle case when no playlist is set
        }
    }

    void Player::PlayNextSong() {
        if (m_playlist != nullptr && m_playlist->GetCollection() != nullptr) {
            m_playlist->IncrementCurrentSongIndex();
            m_songBeingPlayed = m_playlist->GetCurrentSong();
            PlayCurrentSong();
        } else {
            //TODO handle case when no playlist is set
        }
    }

    void Player::StopSong() {
        if (m_songBeingPlayed != nullptr) {
            BroadcastPlaybackEvent(PlaybackEventType::playbackStopped);
            BASS_ChannelStop(m_songBeingPlayed->GetMusicHandle());
            m_state = player_state_stopped;
            m_songBeingPlayed->Rewind();
        }
    }

    void Player::PlayCurrentSong() {
        if (m_songBeingPlayed != nullptr) {
            m_state = player_state_playing;
            BASS_ChannelPlay(m_songBeingPlayed->GetMusicHandle(), m_replay);
            BASS_ChannelSetSync(m_songBeingPlayed->GetMusicHandle(), BASS_SYNC_END, 0, &on_playback_end, this);
            GetPlaybackHistory()->GetCollection()->AddSong(m_songBeingPlayed);
            m_songBeingPlayed->GetCurrentPlaybackTime() >= 1
                ? BroadcastPlaybackEvent(PlaybackEventType::playbackResumed)
                : BroadcastPlaybackEvent(PlaybackEventType::playbackStarted);
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
            return m_songBeingPlayed->GetCurrentPlaybackTime() > 0 ? m_songBeingPlayed->GetCurrentPlaybackTime() : 0;
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

    void Player::BroadcastPlaybackEvent(Bassplay::Event::PlaybackEventType eventType) {
        auto event = BassplayPlaybackEvent(eventType);
        BassplayEventDispatcher::Instance().BroadcastEvent<Bassplay::Event::BassplayPlaybackEvent>(
                event);
    }

   Player::~Player() {
        if (m_songBeingPlayed != nullptr) {
            m_songBeingPlayed->UnloadSong();
            delete m_songBeingPlayed;
            m_songBeingPlayed = nullptr;
        }
        delete m_history_collection;
    }
} // Play