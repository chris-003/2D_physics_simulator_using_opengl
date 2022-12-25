cmake_minimum_required(VERSION 3.24)

project(SResourceCompiler LANGUAGES CXX)
aux_source_directory(./src srcs)

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(SResourceCompiler ${srcs})

target_link_libraries(SResourceCompiler PUBLIC ${Boost_LIBRARIES} boost_filesystem)

aux_source_directory(./lib lib_srcs)
add_library(SResourceData ${lib_srcs})
include_directories(./)

function(add_resource target resources)
    foreach(res ${resources})
        # execute_process(COMMAND SResourceCompiler ${res} -o ${CMAKE_BINARY_DIR}/${res}.cpp
        #     COMMAND_ERROR_IS_FATAL ANY)
        add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${res}.cpp
            COMMAND SResourceCompiler ${CMAKE_CURRENT_SOURCE_DIR}/${res} -o ${CMAKE_CURRENT_BINARY_DIR}/${res}.cpp
            DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${res} SResourceCompiler)
        target_sources(${target} PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/${res}.cpp)
    endforeach()
endfunction()
set(SRCC_INCLUDE_PATH ${CMAKE_CURRENT_LIST_DIR}/include/ CACHE PATH "include path for libsrcc")