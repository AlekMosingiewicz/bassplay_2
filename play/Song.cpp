//
// Created by aleksander on 29.05.22.
//

#include "Song.h"
#include <cstring>
#include <algorithm>

namespace Bassplay::Play {
    Song::Song(std::string &t_path) : m_path(t_path) {
        mHmusic = BASS_MusicLoad(false, t_path.c_str(), 0, 0, BASS_MUSIC_PRESCAN, 0);
        if (mHmusic != 0) {
            Init(mHmusic);
            SetFilename();
        } else {
            throw BassplayException(BASS_ErrorGetCode());
        }
    }

    double Song::GetLength() const {
        QWORD length = BASS_ChannelGetLength(mHmusic, BASS_POS_BYTE);
        return BASS_ChannelBytes2Seconds(mHmusic, length);
    }

    void Song::PopulateSamples() {
        const char *original_sample = BASS_ChannelGetTags(mHmusic, BASS_TAG_MUSIC_SAMPLE);
        int idx = 0;
        while (original_sample != nullptr) {
            size_t original_sample_size = strlen(original_sample);
            char *sample = (char *) malloc(original_sample_size + 1);
            strcpy(sample, original_sample);
            std::string sSample = std::string(sample);
            m_samples.add(sSample);
            original_sample = BASS_ChannelGetTags(mHmusic, BASS_TAG_MUSIC_SAMPLE + (++idx));
        }
    }

    void Song::PopulateInstruments() {
        const char *original_instrument = BASS_ChannelGetTags(mHmusic, BASS_TAG_MUSIC_INST);
        if (original_instrument == NULL) return;
        int idx = 0;
        while (original_instrument != nullptr) {
            size_t original_instrument_size = strlen(original_instrument);
            char *instrument = (char *) malloc(original_instrument_size + 1);
            strcpy(instrument, original_instrument);
            std::string sInstrument = std::string(instrument);
            m_instruments.add(sInstrument);
            original_instrument = BASS_ChannelGetTags(mHmusic, BASS_TAG_MUSIC_INST + (++idx));
        }
    }

    void Song::SetFilename() {
        size_t slashpos = m_path.find_last_of('/');
        size_t flen = m_path.length() - slashpos;
        m_filename = m_path.substr(++slashpos, flen);
    }

    void Song::CleanupBaseData() {
        if (m_info != nullptr) {
            delete (m_info);
        }
    }

    void Song::PopulateMessage() {
        const char *original_message = BASS_ChannelGetTags(mHmusic, BASS_TAG_MUSIC_MESSAGE);
        if (original_message != NULL) {
            m_message = std::string(original_message);
        }
    }

    void Song::SetTitle() {
        const char *original_title = BASS_ChannelGetTags(mHmusic, BASS_TAG_MUSIC_NAME);
        if (strlen(original_title) > 0) {
            m_name = std::string(original_title);
        } else {
            m_name = std::string(BASS_ChannelGetTags(mHmusic, BASS_TAG_MUSIC_NAME));
        }
    }

    void Song::Init(HMUSIC hmusic) {
        m_info = new BASS_CHANNELINFO();
        BASS_ChannelGetInfo(mHmusic, m_info);

        SetTitle();
        PopulateSamples();
        PopulateMessage();
        PopulateInstruments();
    }

    float Song::GetVolume() {
        float returnValue = 0;
        BASS_ChannelGetAttribute(mHmusic, BASS_ATTRIB_VOL, &returnValue);
        return returnValue;
    }

    void Song::SetVolume(float volume) {
        BASS_ChannelSetAttribute(mHmusic, BASS_ATTRIB_VOL, volume);
    }

    std::string Song::GetHumanReadablePlaybackTime() const {
        double lengthInSecs = GetLength();

        int mins = (int) lengthInSecs / 60;
        int secs = (int) lengthInSecs % 60;

        char temp[6];

        sprintf(temp, "%02d:%02d", mins, secs);

        return {temp};
    }

} // Play

