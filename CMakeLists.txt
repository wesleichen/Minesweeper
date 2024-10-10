cmake_minimum_required(VERSION 3.27)
project(minesweeper)
set(CMAKE_CXX_STANDARD 17)

set(SFML_DIR "C:/Libraries/SFML-2.5.1/lib/cmake/SFML")
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(minesweeper
        minesweeper.h
        minesweeper.cpp
        Tile.h
        Button.h
        Tile.cpp
        Button.cpp
        GameState.cpp
        Toolbox.cpp
)
target_link_libraries(minesweeper sfml-graphics sfml-audio)
