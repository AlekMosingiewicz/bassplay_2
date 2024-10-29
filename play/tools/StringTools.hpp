//
// Created by aleksander on 29.10.24.
//

#ifndef BASSPLAY_2_STRINGTOOLS_HPP
#define BASSPLAY_2_STRINGTOOLS_HPP

#include <string>

namespace Bassplay::Play::Tools {

    class StringTools {
    public:
        StringTools() = default;
        [[nodiscard]] static std::string SanitizeString(std::string &str);
    };

}
#endif //BASSPLAY_2_STRINGTOOLS_HPP
