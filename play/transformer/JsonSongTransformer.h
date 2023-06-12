//
// Created by aleksander on 11.06.23.
//

#ifndef BASSPLAY_2_JSONSONGTRANSFORMER_H
#define BASSPLAY_2_JSONSONGTRANSFORMER_H

#include "ISongTransformer.h"

namespace Bassplay::Play::Transformer {

    class JsonSongTransformer: public ISongTransformer {
    public:
        JsonSongTransformer() = default;
        Bassplay::Play::Song Transform(const char* src) override;
    };

} // Bassplay

#endif //BASSPLAY_2_JSONSONGTRANSFORMER_H
