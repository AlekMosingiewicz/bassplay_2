
project(Play)

set(HEADER_FILES
        serializer/ISerializable.h
        serializer/SerializableStringList.hpp
        serializer/ISongSerializer.hpp
        Player.hpp
        Song.hpp
        collection/SongCollection.hpp
        serializer/ISongSerializer.hpp
        serializer/JsonSongSerializer.hpp
        serializer/InvalidSerializerException.h
        transformer/CollectionDataSource.h
        parser/JsonNode.h
        history/history.hpp
        persistence/PlaybackHistoryPersister.cpp
        persistence/PlaybackHistoryPersister.hpp
        tools/StringTools.cpp
        tools/StringTools.hpp
)

set(SOURCE_FILES
        serializer/SerializableStringList.cpp
        Player.cpp
        Song.cpp
        collection/SongCollection.cpp
        serializer/JsonSongSerializer.cpp
        serializer/InvalidSerializerException.cpp
        serializer/InvalidSerializerException.h
        transformer/CollectionDataSource.h
        transformer/ISongCollectionTransformer.h transformer/JsonSongCollectionTransformer.cpp transformer/JsonSongCollectionTransformer.h parser/JsonParser.cpp parser/JsonParser.h parser/JsonNode.h
        history/history.cpp
        transformer/JsonSongTransformer.cpp
        transformer/JsonSongTransformer.hpp
        persistence/PlaybackHistoryPersister.cpp
        persistence/PlaybackHistoryPersister.hpp
        tools/StringTools.cpp
        tools/StringTools.hpp)

add_library(Play_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})