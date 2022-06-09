cmake_minimum_required(VERSION 3.22)
project(bassplay_2)

set(CMAKE_CXX_STANDARD 17)

add_executable(bassplay_2 main.cpp play/Song.cpp play/Song.h play/Player.cpp play/Player.h)

# Add Bass library
add_library( bass SHARED IMPORTED )
set_property(TARGET bass PROPERTY IMPORTED_LOCATION "/usr/local/lib/bass/libbass.so")
target_link_libraries(bassplay_2 bass)

# Add WxWidgets library
find_package(wxWidgets REQUIRED COMPONENTS net core base)
include(${wxWidgets_USE_FILE})
target_link_libraries(bassplay_2 ${wxWidgets_LIBRARIES})