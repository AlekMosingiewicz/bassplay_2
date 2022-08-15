
project(Play)

set(HEADER_FILES
        serializer/ISerializable.h
        serializer/SerializableStringList.h
        Player.h
        Song.h
        )

set(SOURCE_FILES
        serializer/SerializableStringList.cpp
        Player.cpp
        Song.cpp
        )

add_library(Play_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})