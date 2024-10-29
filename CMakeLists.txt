cmake_minimum_required(VERSION 3.22)
project(bassplay_2)

set(CMAKE_CXX_STANDARD 17)

include_directories(play)
add_subdirectory(play)

add_executable(
        bassplay_2
        common/wx.h
        main.cpp
        app/BassplayApp.cpp
        app/BassplayApp.hpp
        ui/PlayerFrame.cpp
        ui/PlayerFrame.h
        exception/BassplayException.h
        thread/GuiThread.cpp
        thread/GuiThread.h
        ui/SongInfoFrame.cpp ui/SongInfoFrame.h
        ui/SongInfoFrame.cpp ui/SongInfoFrame.cpp
        exception/BassplayException.h
        common/wx.h
        ui/DpiAwareFrame.h
        event/BassplayEvent.h
        event/BassplayEventType.h
        event/IBassplayEventHandler.h
        event/BassplayEventDispatcher.h event/BassplayEventDispatcher.cpp
        event/BassplayPlaybackEvent.h
        listener/GuiThreadPauseListener.h listener/GuiThreadPauseListener.cpp
        json/json.hpp
)

# Add Bass library
add_library(bass SHARED IMPORTED exception/BassplayException.h common/wx.h
        event/BassplayEventDispatcher.cpp
        event/BassplayEventDispatcher.h
        event/IBassplayEventHandler.h
        listener/GuiThreadPauseListener.cpp
)
set_property(TARGET bass PROPERTY IMPORTED_LOCATION "/usr/local/lib/bass/libbass.so")
target_link_libraries(bassplay_2 bass Play_lib)

# Add WxWidgets library
find_package(wxWidgets REQUIRED COMPONENTS net core base)
include(${wxWidgets_USE_FILE})
target_link_libraries(bassplay_2 ${wxWidgets_LIBRARIES})

# Copy icon images to hidden app directory
file(MAKE_DIRECTORY "$ENV{HOME}/.bassplay/img")
configure_file("img/211876_play_icon.png" "$ENV{HOME}/.bassplay/img/211876_play_icon.png" COPYONLY)
configure_file("img/211871_pause_icon.png" "$ENV{HOME}/.bassplay/img/211871_pause_icon.png" COPYONLY)
configure_file("img/2203518_block_cube_music_square_stop_icon.png" "$ENV{HOME}/.bassplay/img/2203518_block_cube_music_square_stop_icon.png" COPYONLY)
configure_file("img/3516631_audio_control_gauge_media_play_icon.png" "$ENV{HOME}/.bassplay/img/3516631_audio_control_gauge_media_play_icon.png" COPYONLY)
