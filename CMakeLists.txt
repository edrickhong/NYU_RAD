
cmake_minimum_required(VERSION 3.9)
project(RAD)

#Output directory variables
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

file(GLOB SCREEN src/screen.cpp)


# This will probably not be an exectuable
add_executable(screen ${SCREEN})
