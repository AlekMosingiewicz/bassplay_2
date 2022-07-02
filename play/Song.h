//
// Created by aleksander on 29.05.22.
//

#ifndef BASSPLAY_2_SONG_H
#define BASSPLAY_2_SONG_H

#include <bass/bass.h>
#include <string>
#include <vector>
#include "../exception/BassplayException.h"

namespace Bassplay::Play {

    class Song {
    private:
        HMUSIC m_hmusic = 0;
        BASS_CHANNELINFO *m_info = nullptr;
        std::vector<char *> m_samples;
        std::vector<char *> m_instruments;
        char *m_message = nullptr;
        std::string m_name;
        std::string m_path;
        std::string m_filename;

        void CleanupBaseData();
        void PopulateSamples();
        void CleanupSamples();
        void PopulateMessage();
        void PopulateInstruments();
        void SetTitle();
        void Init(HMUSIC hmusic);
        void SetFilename();

    public:
        Song(HMUSIC music) : m_hmusic(music) { Init(m_hmusic); };
        Song(std::string &path);

        ~Song() {
            CleanupBaseData();
            CleanupSamples();
        }

        double Length();

        std::string GetName() { return BASS_ChannelGetTags(m_hmusic, BASS_TAG_MUSIC_NAME); };

        std::string GetTitle() { return !(m_name.empty()) ? m_name : m_filename; }
        std::string GetFilename() { return m_filename; }

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
