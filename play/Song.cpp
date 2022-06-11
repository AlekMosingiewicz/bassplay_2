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
        int n = -1;
        const char* original_sample = BASS_ChannelGetTags(hmusic, BASS_TAG_MUSIC_SAMPLE);
        while (*original_sample) {
            size_t original_sample_size = strlen(original_sample);
            char *sample = (char *) malloc(original_sample_size + 1);
            std::memset(sample, 0, original_sample_size + 1);
            std::memcpy(sample, original_sample, original_sample_size);
            samples.push_back(sample);
            original_sample += original_sample_size + 1;
        }
    }

    void Song::CleanupSamples() {
        std::for_each(samples.begin(), samples.end(), [](char *sample) { free(sample); });
        samples.clear();
    }

    void Song::CleanupBaseData() {
        if (message != nullptr) {
            delete(message);
        }
        if (name != nullptr) {
            delete(name);
        }
        if (info != nullptr) {
            delete(info);
        }
    }

    void Song::PopulateMessage() {
        const char *original_message = BASS_ChannelGetTags(hmusic, BASS_TAG_MUSIC_MESSAGE);
        if (original_message == NULL) {
            return;
        }
        size_t original_message_size = strlen(original_message);
        char *local_message = (char *) malloc(original_message_size + 1);
        std::memset(local_message, 0, original_message_size + 1);
        std::memcpy(local_message, original_message, original_message_size);
        message = local_message;
    }

    void Song::SetTitle() {
        const char *original_title = BASS_ChannelGetTags(hmusic, BASS_TAG_MUSIC_NAME);
        if (*original_title) {
            name = original_title;
        } else {
            name = info->filename;
        }
    }
} // Play

