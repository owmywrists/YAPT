cmake_minimum_required(VERSION 3.8)
project(YAPT)

find_package(SDL2 REQUIRED)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lSDL")
if(OPENMP_FOUND)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()
set(CMAKE_CXX_FLAGS "-fopenmp")
include_directories(SYSTEM ${OpenMP_INCLUDE_PATH})

include_directories("${PROJECT_BINARY_DIR}")
link_directories("${PROJECT_BINARY_DIR}")

file(GLOB_RECURSE pt_src "src/*.cpp" "src/*.h")

add_executable(YAPT ${pt_src})
target_link_libraries(YAPT SDL2main SDL2)
