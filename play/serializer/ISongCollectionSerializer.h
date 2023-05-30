//
// Created by aleksander on 29.08.22.
//

#ifndef BASSPLAY_2_ISONGCOLLECTIONSERIALIZER_H
#define BASSPLAY_2_ISONGCOLLECTIONSERIALIZER_H

#include "../collection/SongCollection.h"

namespace Bassplay::Play::Collection {
    class SongCollection;
}

namespace Bassplay::Play::Serializer {

    class ISongCollectionSerializer {
    public:
        ISongCollectionSerializer() = default;
        virtual std::string Serialize(Collection::SongCollection* p_songCollection) = 0;
    };

} // Bassplay

#endif //BASSPLAY_2_ISONGCOLLECTIONSERIALIZER_H
