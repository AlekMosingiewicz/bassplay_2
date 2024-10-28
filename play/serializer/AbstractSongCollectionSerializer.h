//
// Created by aleksander on 29.08.22.
//

#ifndef BASSPLAY_2_ABSTRACTSONGCOLLECTIONSERIALIZER_H
#define BASSPLAY_2_ABSTRACTSONGCOLLECTIONSERIALIZER_H

#include "ISongCollectionSerializer.hpp"
#include "ISongSerializer.hpp"
#include "InvalidSerializerException.h"

namespace Bassplay::Play::Serializer {
    class AbstractSongCollectionSerializer: public ISongCollectionSerializer {
    protected:
        ISongSerializer *m_songSerializer;
        virtual void ValidateSerializer() = 0;
    public:
        AbstractSongCollectionSerializer() = default;
        AbstractSongCollectionSerializer(ISongSerializer *p_songSerializer): m_songSerializer(p_songSerializer)  {};
    };
} // Serializer

#endif //BASSPLAY_2_ABSTRACTSONGCOLLECTIONSERIALIZER_H
