
project(Play)

set(HEADER_FILES
        serializer/ISerializable.hpp
        serializer/SerializableStringList.hpp
        serializer/ISongSerializer.hpp
        Player.hpp
        Song.hpp
        collection/SongCollection.hpp
        serializer/ISongSerializer.hpp
        serializer/JsonSongSerializer.hpp
        serializer/InvalidSerializerException.hpp
        history/history.hpp
        persistence/PlaybackHistoryPersister.cpp
        persistence/PlaybackHistoryPersister.hpp
        tools/StringTools.cpp
        tools/StringTools.hpp
        history/facade.cpp
        history/facade.hpp
        history/HistoryDirNotFoundException.hpp
        playlist/BassplayPlaylist.hpp
        persistence/BulkPlaylistsPersister.hpp
        playlist/Manager.hpp
        provider/IPlaylistProvider.hpp
        provider/StandardPlaylistProvider.cpp
        provider/StandardPlaylistProvider.hpp
        provider/factory/PlaylistProviderFactory.hpp
        playlist/factory/ManagerFactory.hpp
)

set(SOURCE_FILES
        serializer/SerializableStringList.cpp
        Player.cpp
        Song.cpp
        collection/SongCollection.cpp
        serializer/JsonSongSerializer.cpp
        serializer/InvalidSerializerException.cpp
        serializer/InvalidSerializerException.hpp
        history/history.cpp
        transformer/JsonSongTransformer.cpp
        transformer/JsonSongTransformer.hpp
        persistence/PlaybackHistoryPersister.cpp
        persistence/PlaybackHistoryPersister.hpp
        tools/StringTools.cpp
        tools/StringTools.hpp
        transformer/JsonPlaylistTransformer.cpp
        transformer/JsonPlaylistTransformer.hpp
        tools/StringTools.hpp
        history/facade.cpp
        history/facade.hpp
        persistence/BulkPlaylistsPersister.cpp
        playlist/Manager.hpp
        provider/StandardPlaylistProvider.cpp
        provider/StandardPlaylistProvider.hpp
)

add_library(Play_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})