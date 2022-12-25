cmake_minimum_required(VERSION 3.24)

project(test LANGUAGES CXX)

find_package(Boost REQUIRED)
find_package(glbinding REQUIRED)
find_package(glfw3 REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
# include_directories(${ENGINE_INCLUDE_PATH})
include_directories(${SRCC_INCLUDE_PATH})
include_directories(${ENGINE_INCLUDE_PATH})

# add_compile_options("-DDMALLOC_FUNC_CHECK")


add_executable(test ${CMAKE_CURRENT_SOURCE_DIR}/test.cpp)
target_compile_features(test PUBLIC cxx_std_20)

target_link_libraries(test PUBLIC ${Boost_LIBRARIES} boost_filesystem)
# target_link_libraries(test PUBLIC engine)
target_link_libraries(test PUBLIC glbinding::glbinding glbinding::glbinding-aux)
target_link_libraries(test PUBLIC glfw)
target_link_libraries(test PUBLIC engine)
# target_link_libraries(test PUBLIC dmallocxx)
