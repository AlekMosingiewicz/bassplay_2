//
// Created by aleksander on 28.10.24.
//

#ifndef BASSPLAY_2_JSONSONGTRANSFORMER_HPP
#define BASSPLAY_2_JSONSONGTRANSFORMER_HPP

#include <string>
#include "../Song.hpp"
#include "../../json/json.hpp"
#include "../tools/StringTools.hpp"

namespace Bassplay::Play::Transformer {

    using json = nlohmann::json;
    using StringTools = Bassplay::Play::Tools::StringTools;

    class JsonSongTransformer {
    public:
        JsonSongTransformer() = default;
        [[nodiscard]] static json TransformToJson(Song *song);
        [[nodiscard]] static Song* TransformFromJson(std::string &json);
    };
}
#endif //BASSPLAY_2_JSONSONGTRANSFORMER_HPP
