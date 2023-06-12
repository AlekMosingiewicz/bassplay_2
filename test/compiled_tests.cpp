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
#include "../play/serializer/SerializableStringList.h"
#include "../play/Song.h"
#include "../play/serializer/JsonSongSerializer.h"
#include "../play/serializer/JsonSongCollectionSerializer.h"
#include "../play/persistence/FileCollectionPersister.h"
#include "../play/parser/JsonParser.h"
#include <fstream>

#include "catch.hpp"

TEST_CASE("String list is properly deserialized")
{
    Bassplay::Play::Serializer::SerializableStringList list;
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

TEST_CASE("Song collection is properly serialized to JSON")
{
    Bassplay::Play::Song song1;
    Bassplay::Play::Song song2;
    Bassplay::Play::Collection::SongCollection collection;
    Bassplay::Play::Serializer::JsonSongSerializer songSerializer;
    Bassplay::Play::Serializer::JsonSongCollectionSerializer serializer(&songSerializer);

    song1.SetName("song1");
    song1.SetFilename("Song1");
    song1.SetPath("/Path/To/Song1");

    song2.SetName("song2");
    song2.SetPath("/Path/To/Song2");
    song2.SetFilename("Song2");

    collection.AddSong(&song1);
    collection.AddSong(&song2);

    std::string json = serializer.Serialize(collection);

    CHECK(json == std::string("[{\"filename\":\"Song1\",\"title\":\"song1\",\"path\":\"/Path/To/Song1\"},{\"filename\":\"Song2\",\"title\":\"song2\",\"path\":\"/Path/To/Song2\"}]"));
}


TEST_CASE("Song collection is properly persisted")
{
    const char* filename = "./test.json";
    std::fstream fstream = std::fstream(filename, std::ios::out);

    Bassplay::Play::Song song1;
    Bassplay::Play::Song song2;
    Bassplay::Play::Collection::SongCollection collection;
    Bassplay::Play::Serializer::JsonSongSerializer songSerializer;
    Bassplay::Play::Serializer::JsonSongCollectionSerializer serializer(&songSerializer);

    song1.SetName("song1");
    song1.SetFilename("Song1");
    song1.SetPath("/Path/To/Song1");

    song2.SetName("song2");
    song2.SetPath("/Path/To/Song2");
    song2.SetFilename("Song2");

    collection.AddSong(&song1);
    collection.AddSong(&song2);

    Bassplay::Play::Persistence::FileCollectionPersister persister(&fstream, &serializer);

    persister.PersistCollection(collection);
    fstream.close();

    std::fstream instream(filename);
    std::string json;

    instream >> json;
    CHECK(json == std::string("[{\"filename\":\"Song1\",\"title\":\"song1\",\"path\":\"/Path/To/Song1\"},{\"filename\":\"Song2\",\"title\":\"song2\",\"path\":\"/Path/To/Song2\"}]"));
    std::remove(filename);
}

TEST_CASE("JSON is properly parsed")
{
    std::string json(R"([{"key1":"value1","key2":"value2","key3":"value3"},{"key4":"value4"}])");
    Bassplay::Play::Parser::JsonParser jsonParser;

    jsonParser.Parse(json);
    std::vector<std::unordered_map<std::string,std::string >> data = jsonParser.GetData();

    std::unordered_map<std::string,std::string> firstObjectData = data.front();
    CHECK("value1" == firstObjectData["key1"]);
    CHECK("value2" == firstObjectData["key2"]);

    std::unordered_map<std::string,std::string> secondObjectData = data.back();
    CHECK("value4" == secondObjectData["key4"]);
}