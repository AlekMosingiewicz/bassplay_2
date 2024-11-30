//
// Created by aleksander on 30.11.24.
//

#ifndef BASSPLAY_2_JSONPLAYLISTTRANSFORMER_HPP
#define BASSPLAY_2_JSONPLAYLISTTRANSFORMER_HPP

#include "../playlist/Playlist.hpp"
#include "../../json/json.hpp"
#include "JsonSongTransformer.hpp"
#include <string>

namespace Bassplay::Play::Transformer {

    using json = nlohmann::json;

    class JsonPlaylistTransformer {
    public:
        JsonPlaylistTransformer() = default;

        [[nodiscard]] static json TransformToJson(Playlist *playlist);

        [[nodiscard]] static Playlist *TransformFromJson(std::string &json);
    };
}

#endif //BASSPLAY_2_JSONPLAYLISTTRANSFORMER_HPP
