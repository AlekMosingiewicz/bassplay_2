//
// Created by aleksander on 28.10.24.
//

#ifndef BASSPLAY_2_PLAYBACKHISTORYPERSISTER_HPP
#define BASSPLAY_2_PLAYBACKHISTORYPERSISTER_HPP

#include "../history/history.hpp"
#include "../../json/json.hpp"
#include <ostream>

namespace Bassplay::Play::Persistence {

    using namespace Bassplay::Play::History;
    using json = nlohmann::json;

    class PlaybackHistoryPersister {
    private:
        std::ostream *m_ostream;
    public:
        PlaybackHistoryPersister(std::ostream *ostream) : m_ostream(ostream) {};
        ~PlaybackHistoryPersister() = default;

        void persist(const PlaybackHistory *history);
    };
}
#endif //BASSPLAY_2_PLAYBACKHISTORYPERSISTER_HPP
