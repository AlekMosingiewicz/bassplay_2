//
// Created by aleksander on 10.06.23.
//

#ifndef BASSPLAY_2_FILECOLLECTIONPERSISTER_H
#define BASSPLAY_2_FILECOLLECTIONPERSISTER_H

#include "AbstractCollectionPersister.h"
#include "../serializer/ISongCollectionSerializer.h"
#include <fstream>

namespace Bassplay::Play::Persistence {

    class FileCollectionPersister: public AbstractCollectionPersister {
    public:
        FileCollectionPersister(std::fstream *fstream, Serializer::ISongCollectionSerializer *serializer)
                : AbstractCollectionPersister(fstream, serializer) {};
        void PersistCollection(Collection::SongCollection *collection) override;
    };

} // Bassplay

#endif //BASSPLAY_2_FILECOLLECTIONPERSISTER_H
