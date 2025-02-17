//
// Created by aleksander on 17.02.25.
//

#include "util.hpp"

#include <fstream>
#include <pwd.h>
#include <unistd.h>

namespace Bassplay::Play::History {


    std::string Util::GetAppDir() {
        struct passwd *pw = getpwuid(getuid());
        const char *homedir = pw->pw_dir;
        std::string basePath(homedir);
        basePath += "/.bassplay";
        return basePath;
    }

    void Util::InitHistoryDir() {
        auto dirPath = GetAppDir();
        if (!std::filesystem::exists(dirPath)) {
            std::filesystem::create_directory(dirPath);
        }
    }

    PlaybackHistory* Util::InitHistory() {
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
}