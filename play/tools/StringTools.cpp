//
// Created by aleksander on 29.10.24.
//

#include "StringTools.hpp"

namespace Bassplay::Play::Tools {

    std::string StringTools::SanitizeString(std::string &str) {
        if (!str.empty() && str.front() == '\"' && str.back() == '\"') {
            str = str.substr(1, str.size() - 2);
        }
        return str;
    }
}