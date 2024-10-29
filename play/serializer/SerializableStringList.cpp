//
// Created by aleksander on 24.07.22.
//

#include "SerializableStringList.hpp"

namespace Bassplay::Play::Serializer {

    std::string SerializableStringList::serialize() {
        std::string output;
        std::list<std::string>::const_iterator it;
        const char delimiter = '\n';

        for (it = m_strings.begin(); it != m_strings.end(); it++) {
            output += (*it);
            if (std::next(it) != m_strings.end()) {
                output += delimiter;
            }
        }

        return output;
    }
} // Bassplay