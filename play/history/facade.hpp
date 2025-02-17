//
// Created by aleksander on 17.02.25.
//

#ifndef BASSPLAY_2_FACADE_HPP
#define BASSPLAY_2_FACADE_HPP

#include <string>
#include <filesystem>
#include "history.hpp"
#include "HistoryDirNotFoundException.hpp"
#include "../persistence/PlaybackHistoryPersister.hpp"

namespace Bassplay::Play::History {
    using Bassplay::Play::History::PlaybackHistory;
    using Bassplay::Play::Persistence::PlaybackHistoryPersister;

    const int HISTORY_SIZE = 5;

    class Facade {
    public:
        static void SaveHistory(PlaybackHistory *history);

        static PlaybackHistory* InitHistory();

        static void InitHistoryDir();

        static std::string GetAppDir();
    };
}


#endif //BASSPLAY_2_FACADE_HPP
