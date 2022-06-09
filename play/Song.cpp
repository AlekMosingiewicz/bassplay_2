//
// Created by aleksander on 29.05.22.
//

#include "Song.h"
#include <cstring>
#include <algorithm>

namespace Bassplay::Play {
    double Song::Length() {
        QWORD length = BASS_ChannelGetLength(hmusic, BASS_POS_BYTE);
        return BASS_ChannelBytes2Seconds(hmusic, length);
    }

    void Song::PopulateSamples() {
        int n = 1;

        while (BASS_ChannelGetTags(hmusic, BASS_TAG_MUSIC_SAMPLE + n) != nullptr) {
            const char *original_sample = BASS_ChannelGetTags(hmusic, BASS_TAG_MUSIC_SAMPLE + n);
            size_t original_sample_size = strlen(original_sample);
            char *sample = (char *) malloc(original_sample_size + 1);
            std::memset(sample, 0, original_sample_size + 1);
            std::memcpy(sample, original_sample, original_sample_size);
            samples.push_back(sample);
        }
    }

    void Song::CleanupSamples() {
        std::for_each(samples.begin(), samples.end(), [](char *sample) { free(sample); });
        samples.clear();
    }

    void Song::PopulateMessage() {
        const char *original_message = BASS_ChannelGetTags(hmusic, BASS_TAG_MUSIC_MESSAGE);
        size_t original_message_size = strlen(original_message);
        char *local_message = (char *) malloc(original_message_size + 1);
        std::memset(local_message, 0, original_message_size + 1);
        std::memcpy(local_message, original_message, original_message_size);
        message = local_message;
    }
} // Play

