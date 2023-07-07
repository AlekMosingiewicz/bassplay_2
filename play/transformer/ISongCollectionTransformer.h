//
// Created by aleksander on 11.06.23.
//

#ifndef BASSPLAY_2_ISONGCOLLECTIONTRANSFORMER_H
#define BASSPLAY_2_ISONGCOLLECTIONTRANSFORMER_H

#include "../collection/SongCollection.h"

namespace Bassplay::Play::Transformer {

    class ISongCollectionTransformer {
    public:
        ISongCollectionTransformer() = default;
        virtual Bassplay::Play::Collection::SongCollection* Transform(const char* src) = 0;
    };

} // Bassplay

#endif //BASSPLAY_2_ISONGCOLLECTIONTRANSFORMER_H
