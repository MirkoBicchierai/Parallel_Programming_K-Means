cmake_minimum_required(VERSION 3.27)
project(Parallel_Programming)

set(CMAKE_CXX_STANDARD 23)

# SFML
set(SFML_INCLUDE_DIR "lib/SFML/include" )
set(SFML_LIBRARY_DIR "lib/SFML/lib")
set(SFML_DIR "lib/SFML/lib/cmake/SFML")

link_directories(SFML_LIBRARY_DIR)
include_directories(SFML_INCLUDE_DIR)

find_package(SFML 2.5.1 COMPONENTS system window graphics network audio REQUIRED)

if(SFML_FOUND)
    message(STATUS "SFML_INCLUDE_DIR: ${SFML_INCLUDE_DIR}")
    message(STATUS "SFML_LIBRARIES: ${SFML_LIBRARIES}")
    message(STATUS "SFML_VERSION: ${SFML_VERSION}")
endif()

#OPENMP
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")

set(SOURCE_FILES_PARALLEL main-parallel.cpp
        Maze.cpp
        Maze.h
        TileBox.cpp
        TileBox.h
)
add_executable(Parallel ${SOURCE_FILES_PARALLEL})
target_link_libraries (Parallel sfml-graphics sfml-window sfml-system sfml-audio)

set(SOURCE_FILES_SEQUENTIAL main-sequential.cpp
        Maze.cpp
        Maze.h
        TileBox.cpp
        TileBox.h
)
add_executable(Sequential ${SOURCE_FILES_SEQUENTIAL})
target_link_libraries (Sequential sfml-graphics sfml-window sfml-system sfml-audio)

