//
// Created by aleksander on 16.08.25.
//

#ifndef BASSPLAY_2_DIRTOOL_HPP
#define BASSPLAY_2_DIRTOOL_HPP

#include <string>
#include "../play/Player.hpp"

namespace Bassplay::Play::Tools {

    using Player = Bassplay::Play::Player;

    class DirTool {
    public:
        static std::string GetSongDirectory(Player *player) {
            return player->HasHistory() && player->GetPlaybackHistory()->GetDir()
            ? (*player->GetPlaybackHistory()->GetDir())
            : player->GetCurrentDirectory();
        }
    };
}

#endif //BASSPLAY_2_DIRTOOL_HPP
