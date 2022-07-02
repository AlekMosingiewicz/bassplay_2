//
// Created by aleksander on 29.05.22.
//

#include "Song.h"
#include <cstring>
#include <algorithm>

namespace Bassplay::Play {
    Song::Song(std::string &path): m_path(path)  {
        m_hmusic = BASS_MusicLoad(false, path.c_str(), 0, 0, BASS_MUSIC_PRESCAN, 0);
        if (m_hmusic != 0) {
            Init(m_hmusic);
            SetFilename();
        } else {
            throw BassplayException(BASS_ErrorGetCode());
        }
    }

    double Song::Length() {
        QWORD length = BASS_ChannelGetLength(m_hmusic, BASS_POS_BYTE);
        return BASS_ChannelBytes2Seconds(m_hmusic, length);
    }

    void Song::PopulateSamples() {
        const char* original_sample = BASS_ChannelGetTags(m_hmusic, BASS_TAG_MUSIC_SAMPLE);
        while (*original_sample) {
            size_t original_sample_size = strlen(original_sample);
            char *sample = (char *) malloc(original_sample_size + 1);
            strcpy(sample, original_sample);
            m_samples.push_back(sample);
            original_sample += original_sample_size + 1;
        }
    }

    void Song::PopulateInstruments() {
        const char* original_instrument = BASS_ChannelGetTags(m_hmusic, BASS_TAG_MUSIC_INST);
        if (original_instrument == NULL) return;
        while (*original_instrument) {
            size_t original_instrument_size = strlen(original_instrument);
            char *instrument = (char*) malloc(original_instrument_size + 1);
            strcpy(instrument, original_instrument);
            m_instruments.push_back(instrument);
            original_instrument += original_instrument_size +1;
        }
    }

    void Song::SetFilename() {
       size_t slashpos = m_path.find_last_of('/');
       size_t flen = m_path.length() - slashpos;
       m_filename = m_path.substr(++slashpos, flen);
    }

    void Song::CleanupSamples() {
        std::for_each(m_samples.begin(), m_samples.end(), [](char *sample) { free(sample); });
        m_samples.clear();
    }

    void Song::CleanupBaseData() {
        if (m_message != nullptr) {
            delete(m_message);
        }
        if (m_info != nullptr) {
            delete(m_info);
        }
    }

    void Song::PopulateMessage() {
        const char *original_message = BASS_ChannelGetTags(m_hmusic, BASS_TAG_MUSIC_MESSAGE);
        if (original_message == NULL) {
            return;
        }
        size_t original_message_size = strlen(original_message);
        char *local_message = (char *) malloc(original_message_size + 1);
        strcpy(local_message, original_message);
        m_message = local_message;
    }

    void Song::SetTitle() {
        const char *original_title = BASS_ChannelGetTags(m_hmusic, BASS_TAG_MUSIC_NAME);
        if (strlen(original_title)>0) {
            m_name = std::string(original_title);
        } else {
            m_name = std::string(BASS_ChannelGetTags(m_hmusic, BASS_TAG_MUSIC_NAME));
        }
    }

    void Song::Init(HMUSIC hmusic) {
        m_info = new BASS_CHANNELINFO();
        BASS_ChannelGetInfo(m_hmusic, m_info);

        SetTitle();
        PopulateSamples();
        PopulateMessage();
        PopulateInstruments();
    }
} // Play

