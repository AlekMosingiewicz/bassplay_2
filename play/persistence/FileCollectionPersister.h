//
// Created by aleksander on 10.06.23.
//

#ifndef BASSPLAY_2_FILECOLLECTIONPERSISTER_H
#define BASSPLAY_2_FILECOLLECTIONPERSISTER_H

#include "AbstractCollectionPersister.h"
#include "../serializer/ISongCollectionSerializer.hpp"
#include "../json/json.hpp"
#include <fstream>

namespace Bassplay::Play::Persistence {

    class FileCollectionPersister: public AbstractCollectionPersister {
    public:
        FileCollectionPersister(std::fstream *fstream, Serializer::ISongCollectionSerializer *serializer)
                : AbstractCollectionPersister(fstream, serializer) {};
        void PersistCollection(const Collection::SongCollection &collection) override;
        const char* GetJsonKey() override { return "history"; }
    };

} // Bassplay

#endif //BASSPLAY_2_FILECOLLECTIONPERSISTER_H
