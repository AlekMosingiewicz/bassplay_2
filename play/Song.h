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
        HMUSIC hmusic;
        BASS_CHANNELINFO *info = nullptr;
        std::vector<char *> samples;
        char *message = nullptr;
        const char *name = nullptr;

        void CleanupBaseData();
        void PopulateSamples();
        void CleanupSamples();
        void PopulateMessage();
        void SetTitle();

    public:
        Song(HMUSIC music) : hmusic(music) {
            info = new BASS_CHANNELINFO();
            BASS_ChannelGetInfo(hmusic, info);

            SetTitle();
            PopulateSamples();
            PopulateMessage();
        };

        ~Song() {
            CleanupBaseData();
            CleanupSamples();
        }

        double Length();

        std::string GetName() { return BASS_ChannelGetTags(hmusic, BASS_TAG_MUSIC_NAME); };

        const char* GetFilename() { return info->filename; }
        const char* GetTitle() { return name; }

        HMUSIC GetMusicHandle() { return hmusic; }
    };
} // Play


#endif //BASSPLAY_2_SONG_H
