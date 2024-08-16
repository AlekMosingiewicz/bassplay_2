
project(Play)

set(HEADER_FILES
        serializer/ISerializable.h
        serializer/SerializableStringList.h
        serializer/ISongSerializer.h
        Player.h
        Song.h
        collection/SongCollection.h
        serializer/ISongSerializer.h
        serializer/JsonSongSerializer.h
        serializer/ISongCollectionSerializer.h
        serializer/JsonSongCollectionSerializer.h
        serializer/AbstractSongCollectionSerializer.h
        serializer/InvalidSerializerException.h
        persistence/FileCollectionPersister.h
        transformer/CollectionDataSource.h
        parser/JsonNode.h
)

set(SOURCE_FILES
        serializer/SerializableStringList.cpp
        Player.cpp
        Song.cpp
        collection/SongCollection.cpp
        serializer/JsonSongSerializer.cpp
        serializer/JsonSongCollectionSerializer.cpp
        serializer/InvalidSerializerException.cpp
        serializer/InvalidSerializerException.h
        persistence/ICollectionPersister.h
        persistence/AbstractCollectionPersister.h
        persistence/FileCollectionPersister.cpp
        persistence/FileCollectionPersister.h
        transformer/CollectionDataSource.h
        transformer/ISongCollectionTransformer.h transformer/JsonSongCollectionTransformer.cpp transformer/JsonSongCollectionTransformer.h parser/JsonParser.cpp parser/JsonParser.h parser/JsonNode.h)

add_library(Play_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})