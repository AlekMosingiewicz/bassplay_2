//
// Created by aleksander on 25.07.22.
//

#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma GCC diagnostic ignored "-Wparentheses"
#endif

#define CATCH_CONFIG_MAIN
#include "../play/serializer/JsonSongSerializer.hpp"
#include "catch.hpp"
#include "playlist/BassplayPlaylist.hpp"
#include "../play/transformer/JsonPlaylistTransformer.hpp"
#include "../play/persistence/BulkPlaylistsPersister.hpp"
#include <list>
#include <fstream>


using namespace Bassplay::Play::Serializer;
using namespace Bassplay::Play::Transformer;
using Bassplay::Play::Song;
using Bassplay::Play::Persistence::BulkPlaylistsPersister;
using std::list;
using std::fstream;

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

TEST_CASE("BassplayPlaylist is properly serialized to JSON")
{
    Bassplay::Play::Playlist::BassplayPlaylist playlist("PlaylistName");
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

TEST_CASE("BassplayPlaylist is properly deserialized from JSON")
{
    auto json = std::string(R"({"name":"PlaylistName","songs":[{"filename":"Song1","path":"Path/To/Song1","title":"SongName1"},{"filename":"Song2","path":"Path/To/Song2","title":"SongName2"}]})");
    auto playlist = JsonPlaylistTransformer::TransformFromJson(json);

    list<Song*> songs = playlist->GetCollection()->GetSongs();

    CHECK(playlist->GetName() == std::string("PlaylistName"));
    CHECK(songs.size() == 2);
    CHECK(songs.front()->GetTitle() == std::string("SongName1"));
    CHECK(songs.front()->GetPath() == std::string("Path/To/Song1"));
    CHECK(songs.back()->GetTitle() == std::string("SongName2"));
    CHECK(songs.back()->GetPath() == std::string("Path/To/Song2"));
}

TEST_CASE("BassplayPlaylist is properly persisted")
{
    auto playlist1 = Bassplay::Play::Playlist::BassplayPlaylist("TestPlaylist1");
    auto song1 = Bassplay::Play::Song();

    auto song1name = std::string ("TestSong1");
    auto song1path = std::string ("Path/To/TestSong1");

    auto song2name = std::string ("TestSong2");
    auto song2path = std::string ("Path/To/TestSong2");

    auto song3name = std::string ("TestSong3");
    auto song3path = std::string ("Path/To/TestSong3");

    auto song4name = std::string ("TestSong4");
    auto song4path = std::string ("Path/To/TestSong4");

    auto expected_json = std::string(R"({"playlists":[{"name":"TestPlaylist1","songs":[{"filename":"TestSong1","path":"Path/To/TestSong1","title":"TestSong1"},{"filename":"TestSong2","path":"Path/To/TestSong2","title":"TestSong2"}]},{"name":"TestPlaylist2","songs":[{"filename":"TestSong3","path":"Path/To/TestSong3","title":"TestSong3"},{"filename":"TestSong4","path":"Path/To/TestSong4","title":"TestSong4"}]}]})");

    song1.SetName(song1name);
    song1.SetPath(song1path);
    playlist1.AddSong(&song1);

    auto song2 = Bassplay::Play::Song();
    song2.SetName(song2name);
    song2.SetPath(song2path);
    playlist1.AddSong(&song2);

    auto playlist2 = Bassplay::Play::Playlist::BassplayPlaylist("TestPlaylist2");
    auto song3 = Bassplay::Play::Song();
    song3.SetName(song3name);
    song3.SetPath(song3path);
    playlist2.AddSong(&song3);

    auto song4 = Bassplay::Play::Song();
    song4.SetName(song4name);
    song4.SetPath(song4path);
    playlist2.AddSong(&song4);

    auto playlists = list<Bassplay::Play::Playlist::BassplayPlaylist*>();
    playlists.push_back(&playlist1);
    playlists.push_back(&playlist2);

    auto destination_path = std::filesystem::current_path();
    destination_path += "/test_playlists.json";

    auto output_stream = fstream(destination_path.c_str(), std::ios::out);
    auto bulk_persister = BulkPlaylistsPersister(&output_stream);
    bulk_persister.persist(playlists);
    output_stream.close();

    auto input_stream = fstream(destination_path, std::ios::in);
    if (!input_stream.is_open()) {
        throw std::runtime_error("Failed to open file for reading: " + destination_path.string());
    }
    std::string json_content((std::istreambuf_iterator<char>(input_stream)), std::istreambuf_iterator<char>());
    input_stream.close();
    CHECK(json_content == expected_json);
    std::filesystem::remove(destination_path);
}