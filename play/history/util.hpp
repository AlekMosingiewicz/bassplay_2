//
// Created by aleksander on 17.02.25.
//

#ifndef BASSPLAY_2_UTIL_HPP
#define BASSPLAY_2_UTIL_HPP

#include <string>
#include <filesystem>
#include "history.hpp"

namespace Bassplay::Play::History {
    using Bassplay::Play::History::PlaybackHistory;

    const int HISTORY_SIZE = 5;

    class Util {
    public:
        static void SaveHistory();

        static PlaybackHistory* InitHistory();

        static void InitHistoryDir();

        static std::string GetAppDir();
    };
}


#endif //BASSPLAY_2_UTIL_HPP
