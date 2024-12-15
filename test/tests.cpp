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
#include "playlist/Playlist.hpp"
#include "../play/transformer/JsonPlaylistTransformer.hpp"


using namespace Bassplay::Play::Serializer;
using namespace Bassplay::Play::Transformer;

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

TEST_CASE("Playlist is properly serialized to JSON")
{
    Bassplay::Play::Playlist::Playlist playlist("PlaylistName");
    Bassplay::Play::Song song1;
    Bassplay::Play::Song song2;

    std::string songName1 = "SongName1";
    std::string songPath1 = "Path/To/Song1";
    std::string songName2 = "SongName2";
    std::string songPath2 = "Path/To/Song2";

    song1.SetName(songName1);
    song1.SetPath(songPath1);
    song2.SetName(songName2);
    song2.SetPath(songPath2);

    playlist.AddSong(&song1);
    playlist.AddSong(&song2);

    std::string json = JsonPlaylistTransformer::TransformToJson(&playlist).dump();

    CHECK(json == std::string("{\"name\":\"PlaylistName\",\"songs\":[{\"filename\":\"Song1\",\"path\":\"Path/To/Song1\",\"title\":\"SongName1\"},{\"filename\":\"Song2\",\"path\":\"Path/To/Song2\",\"title\":\"SongName2\"}]}"));
}