//
// Created by aleksander on 28.10.24.
//

#ifndef BASSPLAY_2_JSONSONGTRANSFORMER_HPP
#define BASSPLAY_2_JSONSONGTRANSFORMER_HPP

#include <string>
#include "../Song.h"
#include "../../json/json.hpp"

namespace Bassplay::Play::Transformer {

    class JsonSongTransformer {
    public:
        JsonSongTransformer() = default;
        [[nodiscard]] static std::string TransformToJson(Song *song);
        [[nodiscard]] static Song* TransformFromJson(std::string &json);
    };
}
#endif //BASSPLAY_2_JSONSONGTRANSFORMER_HPP
