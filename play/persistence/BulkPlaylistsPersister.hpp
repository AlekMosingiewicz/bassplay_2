//
// Created by aleksander on 28.06.25.
//

#ifndef BASSPLAY_2_BULKPLAYLISTSPERSISTER_HPP
#define BASSPLAY_2_BULKPLAYLISTSPERSISTER_HPP

#include <list>
#include "playlist/BassplayPlaylist.hpp"
#include "../transformer/JsonPlaylistTransformer.hpp"

namespace Bassplay::Play::Persistence {

    using Bassplay::Play::Playlist::BassplayPlaylist;
    using Bassplay::Play::Transformer::JsonPlaylistTransformer;

    class BulkPlaylistsPersister {
    private:
        std::ostream *m_ostream;
    public:
         BulkPlaylistsPersister(std::ostream *ostream) : m_ostream(ostream) {};
        /**
         * Persists the given playlist to the specified output stream.
         * @param playlist The playlist to persist.
         */
        void persist(const std::list<BassplayPlaylist*>& playlists);
    };
}

#endif //BASSPLAY_2_BULKPLAYLISTSPERSISTER_HPP
