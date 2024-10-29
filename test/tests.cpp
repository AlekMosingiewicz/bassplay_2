//
// Created by aleksander on 25.07.22.
//

#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma GCC diagnostic ignored "-Wparentheses"
// This one is necessary for the const return non-reference test
#pragma GCC diagnostic ignored "-Wignored-qualifiers"
#endif

#define CATCH_CONFIG_MAIN
#include "../play/serializer/JsonSongSerializer.hpp"
#include "catch.hpp"

using namespace Bassplay::Play::Serializer;

TEST_CASE("String list is properly deserialized")
{
    SerializableStringList list;
    std::string s1("string1");
    std::string s2("string2");
    list.add(s1);
    list.add(s2);
    std::string serialized = list.serialize();
    CHECK(serialized == std::string("string1\nstring2"));
}

TEST_CASE("Song is properly serialized to JSON")
{
    Bassplay::Play::Song song;
    Bassplay::Play::Serializer::JsonSongSerializer serializer;

    std::string songName = "SongName";
    std::string songPath = "Path/To/Song";

    song.SetName(songName);
    song.SetPath(songPath);

    std::string json = serializer.Serialize(&song);

    CHECK(json == std::string("{\"filename\":\"Song\",\"title\":\"SongName\",\"path\":\"Path/To/Song\"}"));
}