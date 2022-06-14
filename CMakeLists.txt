cmake_minimum_required(VERSION 3.2)

project(test)

include_directories(./)
SET(CMAKE_BUILD_TYPE "Debug")

add_subdirectory(engine)
add_subdirectory(glad)
add_subdirectory(application)
