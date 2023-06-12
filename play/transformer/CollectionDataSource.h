//
// Created by aleksander on 11.06.23.
//

#ifndef BASSPLAY_2_COLLECTIONDATASOURCE_H
#define BASSPLAY_2_COLLECTIONDATASOURCE_H

#include <iostream>

namespace Bassplay::Play::Transformer {

    class CollectionDataSource {
    public:
        CollectionDataSource(std::iostream* iostream) { m_iostream = iostream; };
        void Get(std::string &dest) { (*m_iostream) >> dest; };
        void Set(const std::string &src) { (*m_iostream) << src; };
    protected:
        std::iostream* m_iostream;
    };


} // Bassplay

#endif //BASSPLAY_2_COLLECTIONDATASOURCE_H
