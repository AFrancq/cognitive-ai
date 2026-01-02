cmake_minimum_required(VERSION 4.2.0)
project(HaveYouHeardOfChef)

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

add_executable(chef src/main.cpp)
target_link_libraries(chef PRIVATE rtaudio)