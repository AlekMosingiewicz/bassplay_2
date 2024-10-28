//
// Created by aleksander on 10.06.23.
//

#include "FileCollectionPersister.h"

using json = nlohmann::json;

namespace Bassplay::Play::Persistence {
    void FileCollectionPersister::PersistCollection(const Collection::SongCollection &collection) {
        auto serializedCollection = m_serializer->Serialize(collection);
        json history = json::parse(serializedCollection);
        json settings = { {GetJsonKey(), history} };
        std::string settingsString = settings.dump(4);
        m_ostream->write(settingsString.c_str(), (std::streamsize) settingsString.length());
        m_ostream->flush();
    }
} // Bassplay