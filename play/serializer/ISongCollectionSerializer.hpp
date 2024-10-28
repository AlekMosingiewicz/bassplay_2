//
// Created by aleksander on 29.08.22.
//

#ifndef BASSPLAY_2_ISONGCOLLECTIONSERIALIZER_HPP
#define BASSPLAY_2_ISONGCOLLECTIONSERIALIZER_HPP

#include "../collection/SongCollection.hpp"

namespace Bassplay::Play::Collection {
    class SongCollection;
}

namespace Bassplay::Play::Serializer {

    class ISongCollectionSerializer {
    public:
        ISongCollectionSerializer() = default;
        virtual std::string Serialize(const Collection::SongCollection &p_songCollection) = 0;
    };

} // Bassplay

#endif //BASSPLAY_2_ISONGCOLLECTIONSERIALIZER_HPP
