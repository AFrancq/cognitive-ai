cmake_minimum_required(VERSION 4.2.0)
project(HaveYouHeardOfChef)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Setup CPM
file(DOWNLOAD
  https://github.com/cpm-cmake/CPM.cmake/releases/latest/download/CPM.cmake
  ${CMAKE_BINARY_DIR}/CPM.cmake
)
include(${CMAKE_BINARY_DIR}/CPM.cmake)

CPMFindPackage(
  NAME RtAudio
  GITHUB_REPOSITORY thestk/rtaudio
  GIT_TAG 6.0.1
)

# Source files
set(SOURCES
  src/main.cpp
  src/bodypart.cpp
  src/body.cpp
  src/brain.cpp
  src/ear.cpp
)

add_executable(chef ${SOURCES})
target_include_directories(chef PRIVATE 
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_BINARY_DIR}/_deps/rtaudio-src
)
target_link_libraries(chef PRIVATE rtaudio)