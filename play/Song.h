//
// Created by aleksander on 29.05.22.
//

#ifndef BASSPLAY_2_SONG_H
#define BASSPLAY_2_SONG_H

#include <bass/bass.h>
#include <string>
#include <vector>
#include "../exception/BassException.h"

namespace Bassplay::Play {

    class Song {
    private:
        HMUSIC hmusic;
        BASS_CHANNELINFO *info;
        std::vector<char *> samples;
        char *message;

        void PopulateSamples();

        void CleanupSamples();

        void PopulateMessage();

    public:
        Song(HMUSIC music) : hmusic(music) {
            info = new BASS_CHANNELINFO();
            BASS_ChannelGetInfo(hmusic, info);
            PopulateSamples();
            PopulateMessage();
        };

        ~Song() {
            CleanupSamples();
        }

        double Length();

        std::string GetName() { return BASS_ChannelGetTags(hmusic, BASS_TAG_MUSIC_NAME); };

        HMUSIC GetMusicHandle() { return hmusic; }
    };
} // Play


#endif //BASSPLAY_2_SONG_H
