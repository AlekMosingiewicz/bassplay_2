//
// Created by aleksander on 11.06.23.
//

#ifndef BASSPLAY_2_ISONGTRANSFORMER_H
#define BASSPLAY_2_ISONGTRANSFORMER_H

#include "../Song.h"

namespace Bassplay::Play::Transformer {

    class ISongTransformer {
    public:
        ISongTransformer() = default;
        virtual Bassplay::Play::Song Transform(const char* src) = 0;
    };

} // Bassplay

#endif //BASSPLAY_2_ISONGTRANSFORMER_H
