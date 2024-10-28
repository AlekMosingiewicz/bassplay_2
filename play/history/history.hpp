//
// Created by aleksander on 28.10.24.
//

#ifndef BASSPLAY_2_HISTORY_HPP
#define BASSPLAY_2_HISTORY_HPP

#include "../collection/SongCollection.h"
#include "../../json/json.hpp"

namespace Bassplay::Play::History {

    using namespace Bassplay::Play::Collection;

    class History {
    public:
        History() = default;
        void SetCollection(SongCollection *collection) { m_collection = collection; }
        void SetLastSong(std::string *lastSong) { m_lastSong = lastSong; }
        [[nodiscard]] SongCollection* GetCollection() const { return m_collection; }
        [[nodiscard]] std::string* GetLastSong() const { return m_lastSong; }
        static History* CreateFromJson(std::string &json);

    private:
        SongCollection *m_collection;
        std::string *m_lastSong;
    };

}
#endif //BASSPLAY_2_HISTORY_HPP
