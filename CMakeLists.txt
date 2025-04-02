cmake_minimum_required(VERSION 3.24)
project(OGGTest LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.0
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
add_executable(OGGTest src/main.cpp
        src/state_machine.cpp
        src/game.cpp
        src/slot_machine/slot_machine.cpp
        src/rect_button.cpp
        src/slot_machine/slot_reel.cpp
        src/slot_machine/slot_symbol.cpp
        src/slot_machine/slot_view.cpp
        src/slot_machine/winning_line.cpp)
target_include_directories(OGGTest PRIVATE include include/slot_machine)
target_link_libraries(OGGTest SFML::Graphics)

