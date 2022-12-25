cmake_minimum_required(VERSION 3.24)

project(engine LANGUAGES CXX C)
aux_source_directory(./src srcs)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
include_directories(${GLFW3_INCLUDE_DIR})
# find_package(Boost REQUIRED)
# include_directories(${Boost_INCLUDE_DIRS})
find_package(box2d REQUIRED)
find_package(glbinding REQUIRED)
include_directories(${SRCC_INCLUDE_PATH})

add_library(engine SHARED ${srcs})
add_resource(engine  ./Resource.rcc)

target_compile_features(engine PUBLIC cxx_std_20)

target_link_libraries(engine PUBLIC glfw)
target_link_libraries(engine PUBLIC ${GLM_LIBRARIES})
# target_link_libraries(engine PUBLIC ${Boost_LIBRARIES})
target_link_libraries(engine PUBLIC box2d::box2d)
target_link_libraries(engine PUBLIC SResourceData)
target_link_libraries(engine PUBLIC glbinding::glbinding glbinding::glbinding-aux)

set(ENGINE_INCLUDE_PATH ${CMAKE_CURRENT_LIST_DIR}/src/ CACHE PATH "include path for libengine")
