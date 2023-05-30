//
// Created by aleksander on 29.08.22.
//

#include "JsonSongSerializer.h"

namespace Bassplay::Play::Serializer {
    std::string JsonSongSerializer::Serialize(Bassplay::Play::Song *p_song) {
        std::string serialized = "{";
        serialized+="\"filename\":\""+p_song->GetFilename()+"\",";
        serialized+="\"title\":\""+p_song->GetTitle()+"\",";
        serialized+="\"path\":\""+p_song->GetPath()+"\"";
        serialized+="}";

        return serialized;
    }
} // Bassplay