//
// Created by aleksander on 10.06.23.
//

#include "FileCollectionPersister.h"

namespace Bassplay::Play::Persistence {
    void FileCollectionPersister::PersistCollection(Collection::SongCollection *collection) {
        std::string serlializedCollection = m_serializer->Serialize(collection);
        m_ostream->write(serlializedCollection.c_str(), (std::streamsize) serlializedCollection.length());
        m_ostream->flush();
    }
} // Bassplay