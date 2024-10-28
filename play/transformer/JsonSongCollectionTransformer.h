//
// Created by aleksander on 11.06.23.
//

#ifndef BASSPLAY_2_JSONSONGCOLLECTIONTRANSFORMER_H
#define BASSPLAY_2_JSONSONGCOLLECTIONTRANSFORMER_H

#include "ISongCollectionTransformer.h"
#include "../parser/JsonParser.h"
#include "../Song.hpp"
#include <map>

namespace Bassplay::Play::Transformer {

    class JsonSongCollectionTransformer: public ISongCollectionTransformer {
    public:
        JsonSongCollectionTransformer(Bassplay::Play::Parser::JsonParser* parser): m_jsonParser(parser) {};
        Bassplay::Play::Collection::SongCollection* Transform(const char* src) override;
    private:
        Bassplay::Play::Song* CreateSong(std::unordered_map<std::string, std::string> data);
        Bassplay::Play::Parser::JsonParser* m_jsonParser;
    };

} // Bassplay

#endif //BASSPLAY_2_JSONSONGCOLLECTIONTRANSFORMER_H
