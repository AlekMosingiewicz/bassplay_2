//
// Created by aleksander on 31.05.23.
//

#ifndef BASSPLAY_2_ICOLLECTIONPERSISTER_H
#define BASSPLAY_2_ICOLLECTIONPERSISTER_H

#include "../collection/SongCollection.h"

namespace Bassplay::Play::Persistence {
    class ICollectionPersister {
    public:
        virtual void PersistCollection(const Bassplay::Play::Collection::SongCollection &collection){};
        virtual const char* GetJsonKey() = 0;
    };
} // Persistence

#endif //BASSPLAY_2_ICOLLECTIONPERSISTER_H
