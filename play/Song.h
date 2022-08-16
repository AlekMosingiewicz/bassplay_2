//
// Created by aleksander on 29.05.22.
//

#ifndef BASSPLAY_2_SONG_H
#define BASSPLAY_2_SONG_H

#include <bass/bass.h>
#include <string>
#include <vector>
#include "../exception/BassplayException.h"
#include "serializer/SerializableStringList.h"

namespace Bassplay::Play {

    class Song {
    private:
        HMUSIC m_hmusic = 0;
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
        Song(HMUSIC t_music) : m_hmusic(t_music) { Init(m_hmusic); };
        Song(std::string &t_path);

        ~Song() {
            CleanupBaseData();
        }

        double GetLength() const;

        std::string GetName() { return BASS_ChannelGetTags(m_hmusic, BASS_TAG_MUSIC_NAME); };

        std::string GetTitle() { return !(m_name.empty()) ? m_name : m_filename; }
        std::string GetFilename() { return m_filename; }
        std::string GetMessage() { return m_message; }
        std::string GetHumanReadableSamples() { return m_samples.serialize(); };
        std::string GetHumanReadableInstruments() { return m_instruments.serialize(); };
        std::string GetHumanReadablePlaybackTime() const;

        void UnloadSong() {
            if (m_hmusic != 0) BASS_MusicFree(m_hmusic);
            m_hmusic = 0;
        }

        void Rewind() {
            BASS_ChannelSetPosition(m_hmusic, MAKELONG(0, 0), BASS_POS_MUSIC_ORDER |
                                                              BASS_MUSIC_POSRESET);
        }

        double GetCurrentPlaybackTime() {
            return BASS_ChannelBytes2Seconds(m_hmusic, BASS_ChannelGetPosition(m_hmusic, BASS_POS_BYTE));
        }

        HMUSIC GetMusicHandle() { return m_hmusic; }
    };
} // Play


#endif //BASSPLAY_2_SONG_H
