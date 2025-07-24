//
// Created by aleksander on 17.07.25.
//

#ifndef BASSPLAY_2_PLAYLISTPROVIDERFACTORY_HPP
#define BASSPLAY_2_PLAYLISTPROVIDERFACTORY_HPP

#include "provider/IPlaylistProvider.hpp"
#include "provider/StandardPlaylistProvider.hpp"

namespace Bassplay::Play::Provider::Factory {

    class PlaylistProviderFactory {
    public:
        static StandardPlaylistProvider *CreateFromPath(const std::string &filePath) {
            auto *inputStream = new std::fstream(filePath, std::ios::in);
            if (!inputStream->is_open()) {
                return new StandardPlaylistProvider();
            }
            return new StandardPlaylistProvider(inputStream);
        }

    };

}
#endif //BASSPLAY_2_PLAYLISTPROVIDERFACTORY_HPP
