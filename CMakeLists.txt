cmake_minimum_required(VERSION 3.15)
project(LearningOpenGL)

set(CMAKE_CXX_STANDARD 17)

add_executable(LearningOpenGL main.cpp Shader.cpp Shader.h Application.cpp Application.h ShaderProgram.cpp ShaderProgram.h)

find_package(glfw3 3.3 REQUIRED)
find_package(GLEW REQUIRED)
target_link_libraries(LearningOpenGL glfw3 GLEW::GLEW)
