//
// Created by aleksander on 29.08.22.
//

#ifndef BASSPLAY_2_JSONSONGSERIALIZER_H
#define BASSPLAY_2_JSONSONGSERIALIZER_H

#include "ISongSerializer.h"

namespace Bassplay::Play::Serializer {

    class JsonSongSerializer: public ISongSerializer {
    public:
        std::string Serialize(Bassplay::Play::Song *p_song) override;
    };

} // Bassplay

#endif //BASSPLAY_2_JSONSONGSERIALIZER_H
