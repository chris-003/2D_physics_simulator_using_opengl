cmake_minimum_required(VERSION 3.2)

project(engine)

file(GLOB engine_src "*.cpp")
# add_library(engine Framebuffer.cpp Shader.cpp ShaderProgram.cpp Timer.cpp VertexArray.cpp VertexBuffer.cpp World.cpp)
add_library(engine ${engine_src})
target_link_libraries(engine glfw GL X11 pthread Xrandr Xi dl box2d)
