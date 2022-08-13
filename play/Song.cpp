//
// Created by aleksander on 29.05.22.
//

#include "Song.h"
#include <cstring>
#include <algorithm>

namespace Bassplay::Play {
    Song::Song(std::string &t_path): m_path(t_path)  {
        m_hmusic = BASS_MusicLoad(false, t_path.c_str(), 0, 0, BASS_MUSIC_PRESCAN, 0);
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
            m_samples.emplace_back(std::string(sample));
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
            m_instruments.emplace_back(std::string(instrument));
            original_instrument += original_instrument_size +1;
        }
    }

    void Song::SetFilename() {
       size_t slashpos = m_path.find_last_of('/');
       size_t flen = m_path.length() - slashpos;
       m_filename = m_path.substr(++slashpos, flen);
    }

    void Song::CleanupBaseData() {
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
        m_message = std::string(local_message);
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

    std::string Song::GetHumanReadableSamples() {
        std::string readableSamples;
        for (std::string sample: m_samples) {
            readableSamples += "\n" + sample;
        }
        return readableSamples;
    }

    std::string Song::GetHumanReadableInstruments() {
        std::string readableInstruments;
        for (std::string instrument: m_instruments) {
            readableInstruments += "\n" + instrument;
        }
        return readableInstruments;
    }
} // Play

