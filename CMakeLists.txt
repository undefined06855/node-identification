cmake_minimum_required(VERSION 3.21)

project(node-identification)

add_library(node-identification INTERFACE)

set_target_properties(node-identification PROPERTIES CXX_VISIBILITY_PRESET hidden)

file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
target_sources(node-identification INTERFACE ${SOURCES})

target_include_directories(node-identification INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
