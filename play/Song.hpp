//
// Created by aleksander on 29.05.22.
//

#ifndef BASSPLAY_2_SONG_HPP
#define BASSPLAY_2_SONG_HPP

#include <bass/bass.h>
#include <string>
#include <vector>
#include "../exception/BassplayException.hpp"
#include "serializer/SerializableStringList.hpp"

namespace Bassplay::Play {

    class Song {
    private:
        HMUSIC mHmusic = 0;
        BASS_CHANNELINFO *m_info = nullptr;
        Serializer::SerializableStringList m_samples;
        Serializer::SerializableStringList m_instruments;
        std::string m_message;
        std::string m_name;
        std::string m_path;
        std::string m_filename;

        void CleanupBaseData();
        void PopulateSamples();
        void PopulateMessage();
        void PopulateInstruments();
        void SetTitle();
        void Init(HMUSIC hmusic);
        void SetFilename();

    public:
        explicit Song(HMUSIC t_music) : mHmusic(t_music) { Init(mHmusic); };
        explicit Song(std::string &t_path);
        Song() = default;

        ~Song() {
            CleanupBaseData();
        }

        [[nodiscard]] double GetLength() const;

        [[nodiscard]] std::string GetName() const { return BASS_ChannelGetTags(mHmusic, BASS_TAG_MUSIC_NAME); };

        std::string GetTitle() { return !(m_name.empty()) ? m_name : m_filename; }
        std::string GetFilename() { return m_filename; }
        std::string GetMessage() { return m_message; }
        std::string GetPath() { return m_path; }
        std::string GetHumanReadableSamples() { return m_samples.serialize(); };
        std::string GetHumanReadableInstruments() { return m_instruments.serialize(); };
        [[nodiscard]] std::string GetHumanReadablePlaybackTime() const;

        void SetName(std::string &p_name) { m_name = p_name; }
        void SetPath(std::string &p_path) { m_path = p_path; SetFilename(); }

        void SetName(const char* name) { m_name = std::string(name); }
        void SetPath(const char* path) { m_path = std::string (path); }
        void SetFilename(const char* filename) { m_filename = std::string(filename); }
        void SetFilename(std::string &filename) { m_filename = filename; }
        float GetVolume();
        void SetVolume(float volume);

        void UnloadSong() {
            if (mHmusic != 0) BASS_MusicFree(mHmusic);
            mHmusic = 0;
        }

        void Rewind() const {
            BASS_ChannelSetPosition(mHmusic, MAKELONG(0, 0), BASS_POS_MUSIC_ORDER |
                                                             BASS_MUSIC_POSRESET);
        }

        [[nodiscard]] double GetCurrentPlaybackTime() const {
            return BASS_ChannelBytes2Seconds(mHmusic, BASS_ChannelGetPosition(mHmusic, BASS_POS_BYTE));
        }

        [[nodiscard]] HMUSIC GetMusicHandle() const { return mHmusic; }
    };
} // Play


#endif //BASSPLAY_2_SONG_HPP
