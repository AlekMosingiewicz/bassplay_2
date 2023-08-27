//
// Created by aleksander on 29.08.22.
//

#ifndef BASSPLAY_2_ISONGSERIALIZER_H
#define BASSPLAY_2_ISONGSERIALIZER_H

#include <string>
#include "../Song.h"

namespace Bassplay::Play {

    class ISongSerializer {
    public:
        ISongSerializer() = default;
        ~ISongSerializer() = default;
        virtual std::string Serialize(Song* p_song) = 0;
    };

} // Bassplay

#endif //BASSPLAY_2_ISONGSERIALIZER_H
