cmake_minimum_required(VERSION 3.24)

project(2D_physics_simulator_using_opengl LANGUAGES CXX C)

add_compile_options("-fPIC")
add_compile_options("-ggdb2")

add_subdirectory(./SResourceCompiler)
add_subdirectory(./engine)
# add_subdirectory(./application)
add_subdirectory(./test)
