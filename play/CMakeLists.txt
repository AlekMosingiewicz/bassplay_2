
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
        serializer/InvalidSerializerException.h)

set(SOURCE_FILES
        serializer/SerializableStringList.cpp
        Player.cpp
        Song.cpp
        collection/SongCollection.cpp
        serializer/JsonSongSerializer.cpp
        serializer/JsonSongCollectionSerializer.cpp
        serializer/InvalidSerializerException.cpp
        serializer/InvalidSerializerException.h)

add_library(Play_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})