cmake_minimum_required(VERSION 3.2)

project(application)

file(GLOB main_src "*.cpp")
add_executable(main ${main_src})
target_link_libraries(main glad engine)
