//
// Created by aleksander on 25.02.24.
//

#ifndef BASSPLAY_2_BASSPLAYPLAYBACKEVENT_H
#define BASSPLAY_2_BASSPLAYPLAYBACKEVENT_H

#include "BassplayEventType.h"
#include "BassplayEvent.h"

namespace Bassplay::Event {

    enum PlaybackEventType {
        playbackStarted,
        playbackStopped
    };

    class BassplayPlaybackEvent : public BassplayEvent {
    public:
        BassplayPlaybackEvent(PlaybackEventType playbackEventType) : BassplayEvent(playbackEvent),
                                                                     m_playbackEventType(playbackEventType) {}

       PlaybackEventType GetPlaybackEventType() { return m_playbackEventType; }
    private:
        PlaybackEventType m_playbackEventType;
    };

}

#endif //BASSPLAY_2_BASSPLAYPLAYBACKEVENT_H
