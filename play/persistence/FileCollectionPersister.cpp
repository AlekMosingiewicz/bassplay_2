//
// Created by aleksander on 10.06.23.
//

#include "FileCollectionPersister.h"

namespace Bassplay::Play::Persistence {
    void FileCollectionPersister::PersistCollection(const Collection::SongCollection &collection) {
        auto serializedCollection = m_serializer->Serialize(collection);
        m_ostream->write(serializedCollection.c_str(), (std::streamsize) serializedCollection.length());
        m_ostream->flush();
    }
} // Bassplay