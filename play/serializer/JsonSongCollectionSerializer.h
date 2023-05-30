//
// Created by aleksander on 29.08.22.
//

#ifndef BASSPLAY_2_JSONSONGCOLLECTIONSERIALIZER_H
#define BASSPLAY_2_JSONSONGCOLLECTIONSERIALIZER_H

#include "AbstractSongCollectionSerializer.h"
#include "JsonSongSerializer.h"

namespace Bassplay::Play::Serializer {

    class JsonSongCollectionSerializer: public AbstractSongCollectionSerializer {
    protected:
        void ValidateSerializer() override;
    public:
        JsonSongCollectionSerializer(JsonSongSerializer* serializer): AbstractSongCollectionSerializer(serializer) {}
        std::string Serialize(Collection::SongCollection *p_songCollection) override;
        ~JsonSongCollectionSerializer() {}
    };
}




#endif //BASSPLAY_2_JSONSONGCOLLECTIONSERIALIZER_H
