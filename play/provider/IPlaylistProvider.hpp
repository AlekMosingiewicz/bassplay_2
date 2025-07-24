//
// Created by aleksander on 29.06.25.
//

#ifndef BASSPLAY_2_IPLAYLISTPROVIDER_HPP
#define BASSPLAY_2_IPLAYLISTPROVIDER_HPP

#include <map>
#include <string>
#include "playlist/BassplayPlaylist.hpp"

namespace Bassplay::Play::Provider {
    using Bassplay::Play::Playlist::BassplayPlaylist;

    class IPlaylistProvider {
    public:
        IPlaylistProvider() = default;

        virtual ~IPlaylistProvider() = default;

        virtual std::map<std::basic_string<char>, BassplayPlaylist *> *GetPlaylists() = 0;
    };
} // Bassplay

#endif //BASSPLAY_2_IPLAYLISTPROVIDER_HPP
