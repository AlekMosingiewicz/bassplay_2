//
// Created by aleksander on 29.06.25.
//

#ifndef BASSPLAY_2_STANDARDPLAYLISTPROVIDER_HPP
#define BASSPLAY_2_STANDARDPLAYLISTPROVIDER_HPP

#include "IPlaylistProvider.hpp"
#include "../transformer/JsonPlaylistTransformer.hpp"
#include <fstream>

namespace Bassplay::Play::Provider {
    using Bassplay::Play::Transformer::JsonPlaylistTransformer;


    class StandardPlaylistProvider : public IPlaylistProvider {
    private:
        std::fstream *m_inputStream;
    public:
        explicit StandardPlaylistProvider(std::fstream *inputStream) : m_inputStream(inputStream) {};
        explicit StandardPlaylistProvider() : m_inputStream(nullptr) {};

        ~StandardPlaylistProvider() override {
            if (m_inputStream != nullptr && m_inputStream->is_open()) {
                m_inputStream->close();
            }
        };

        std::map<std::string, BassplayPlaylist *> *GetPlaylists() override;
    };
} // Bassplay

#endif //BASSPLAY_2_STANDARDPLAYLISTPROVIDER_HPP
