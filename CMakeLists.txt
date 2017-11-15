cmake_minimum_required(VERSION 3.8)
project(pt)

find_package(SDL2 REQUIRED)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lSDL")

include_directories("${PROJECT_BINARY_DIR}")
link_directories("${PROJECT_BINARY_DIR}")

file(GLOB_RECURSE pt_src "src/*.cpp" "src/*.h")

add_executable(pt ${pt_src})
target_link_libraries(pt SDL2main SDL2)
