cmake_minimum_required(VERSION 3.24)

project(applicatoin LANGUAGES CXX)
aux_source_directory(./src srcs)
set(CMAKE_CXX_STANDARD 20)

include_directories(${ENGINE_INCLUDE_PATH})
find_package(box2d REQUIRED)
# find_package(Boost REQUIRED)
# include_directories(${Boost_INCLUDE_DIRS})
include_directories(${SRCC_INCLUDE_PATH})

add_executable(application ${srcs})
add_resource(application ./Resource.rcc)

target_link_libraries(application PUBLIC engine)
target_link_libraries(application PUBLIC box2d::box2d)
# target_link_libraries(engine PUBLIC ${Boost_LIBRARIES})
target_link_libraries(application PUBLIC srcc)
