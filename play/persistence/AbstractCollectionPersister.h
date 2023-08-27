//
// Created by aleksander on 31.05.23.
//

#ifndef BASSPLAY_2_ABSTRACTCOLLECTIONPERSISTER_H
#define BASSPLAY_2_ABSTRACTCOLLECTIONPERSISTER_H

#include "ICollectionPersister.h"
#include "../serializer/ISongCollectionSerializer.h"
#include <ostream>

namespace Bassplay::Play::Persistence {

    class AbstractCollectionPersister: public ICollectionPersister {
    public:
        AbstractCollectionPersister(
                std::ostream* ostream,
                Bassplay::Play::Serializer::ISongCollectionSerializer* serializer): m_ostream(ostream), m_serializer(serializer) {}
    protected:
        std::ostream* m_ostream;
        Bassplay::Play::Serializer::ISongCollectionSerializer *m_serializer;
    };

} // Persistence

#endif //BASSPLAY_2_ABSTRACTCOLLECTIONPERSISTER_H
