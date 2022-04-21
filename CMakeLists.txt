cmake_minimum_required(VERSION 3.5)
project(HexWars)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)
Include(FetchContent)

FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  GIT_TAG        4.0.0
)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.0.0-preview3
)
FetchContent_MakeAvailable(raylib Catch2)

include_directories("src")

# add all sources
file(GLOB SOURCES
	src/tile.h src/tile.cpp
	src/Game.h src/Game.cpp
	src/utils.h
	src/point.h
)

add_executable(HexWars "src/main.cpp" "${SOURCES}")
target_link_libraries(HexWars PUBLIC raylib)

add_executable(TestHexWars tests/test.cpp "${SOURCES}")
target_link_libraries(TestHexWars PRIVATE Catch2::Catch2WithMain)
target_link_libraries(TestHexWars PRIVATE raylib)

