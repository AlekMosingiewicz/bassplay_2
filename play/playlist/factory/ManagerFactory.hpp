//
// Created by aleksander on 24.07.25.
//

#ifndef BASSPLAY_2_MANAGERFACTORY_HPP
#define BASSPLAY_2_MANAGERFACTORY_HPP

#include "../../provider/factory/PlaylistProviderFactory.hpp"
#include "../../persistence/BulkPlaylistsPersister.hpp"

#include "../Manager.hpp"

namespace Bassplay::Play::Playlist::Factory {

    using Bassplay::Play::Playlist::Manager;
    using Bassplay::Play::Provider::Factory::PlaylistProviderFactory;
    using Bassplay::Play::Persistence::BulkPlaylistsPersister;

    /**
     * Factory class for creating playlist managers.
     */
    class ManagerFactory {
    public:
        /**
         * Creates a new playlist manager using the specified file path.
         * @param filePath The path to the playlist file.
         * @return A pointer to the created Manager instance.
         */
        static Manager* CreateFromPath(const std::string &filePath) {
            auto provider = PlaylistProviderFactory::CreateFromPath(filePath);
            auto persister = new BulkPlaylistsPersister(new std::fstream(filePath, std::ios::out | std::ios::trunc));

            return new Manager(provider, persister);
        }
    };
}

#endif //BASSPLAY_2_MANAGERFACTORY_HPP
