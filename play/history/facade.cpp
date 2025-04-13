//
// Created by aleksander on 17.02.25.
//

#include "facade.hpp"

#include <fstream>
#include <pwd.h>
#include <unistd.h>

namespace Bassplay::Play::History {

    std::string Facade::GetAppDir() {
        struct passwd *pw = getpwuid(getuid());
        const char *homedir = pw->pw_dir;
        std::string basePath(homedir);
        basePath += "/.bassplay";
        return basePath;
    }

    void Facade::InitHistoryDir() {
        auto dirPath = GetAppDir();
        if (!std::filesystem::exists(dirPath)) {
            std::filesystem::create_directory(dirPath);
        }
    }

    PlaybackHistory* Facade::InitHistory() {
        auto appDir = GetAppDir();
        if (!std::filesystem::exists(appDir)) {
            InitHistoryDir();
        }
        auto history_path = GetAppDir() + "/history_stream.json";
        if (!std::filesystem::exists(history_path)) {
            return {};
        }
        std::ifstream historyFile(history_path);
        std::string jsonString((std::istreambuf_iterator<char>(historyFile)),
                               std::istreambuf_iterator<char>());

        if (jsonString.empty()) {
            return {};
        }
        auto playbackHistory = PlaybackHistory::CreateFromJson(jsonString);
        playbackHistory->GetCollection()->SetLimit(HISTORY_SIZE);
        return playbackHistory;
    }

    void Facade::SaveHistory(PlaybackHistory *history) {
        InitHistoryDir();
        auto appDir = GetAppDir();
        std::string history_path = appDir + "/history_stream.json";
        std::fstream history_stream(history_path, std::ostream::out);
        PlaybackHistoryPersister persister(&history_stream);
        persister.persist(history);
    }
}