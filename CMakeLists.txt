cmake_minimum_required(VERSION 3.22)
project(bassplay_2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-no-pie")

include_directories(play)
add_subdirectory(play)

add_executable(
        bassplay_2
        common/wx.h
        main.cpp
        app/BassplayApp.cpp
        app/BassplayApp.h
        ui/PlayerFrame.cpp
        ui/PlayerFrame.h
        exception/BassplayException.cpp
        exception/BassplayException.h
        thread/GuiThread.cpp
        thread/GuiThread.h
        ui/SongInfoFrame.cpp ui/SongInfoFrame.h
        ui/SongInfoFrame.cpp ui/SongInfoFrame.cpp
        exception/BassplayException.cpp
        exception/BassplayException.h
        common/wx.h
        )

# Add Bass library
add_library(bass SHARED IMPORTED exception/BassplayException.cpp exception/BassplayException.h common/wx.h)
set_property(TARGET bass PROPERTY IMPORTED_LOCATION "/usr/local/lib/bass/libbass.so")
target_link_libraries(bassplay_2 bass Play_lib)

# Add WxWidgets library
find_package(wxWidgets REQUIRED COMPONENTS net core base)
include(${wxWidgets_USE_FILE})
target_link_libraries(bassplay_2 ${wxWidgets_LIBRARIES})

# Add unit tests
add_subdirectory(test)