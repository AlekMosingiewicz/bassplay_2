//
// Created by aleksander on 29.08.22.
//

#include "JsonSongCollectionSerializer.h"

namespace Bassplay::Play::Serializer {
    void JsonSongCollectionSerializer::ValidateSerializer() {
        if (dynamic_cast<JsonSongSerializer*>(m_songSerializer) == nullptr)
            throw InvalidSerializerException();
    }

    std::string JsonSongCollectionSerializer::Serialize(Collection::SongCollection *p_songCollection) {
        std::string collection_json = "[";
        auto list = p_songCollection->GetSongs();
        auto it = list.rbegin();

        while (it != list.rend()) {
            collection_json += m_songSerializer->Serialize((*it));
            if (++it != list.rend()) {
                collection_json+=",";
            }
        }

        collection_json += "]";

        return collection_json;
    }
}