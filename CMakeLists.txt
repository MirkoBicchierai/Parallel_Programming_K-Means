cmake_minimum_required(VERSION 3.27)
project(Parallel_Programming)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")

set(SOURCE_FILES_PARALLEL main-parallel.cpp)
add_executable(Parallel ${SOURCE_FILES_PARALLEL})

set(SOURCE_FILES_SEQUENTIAL main-sequential.cpp)
add_executable(Sequential ${SOURCE_FILES_SEQUENTIAL})

