cmake_minimum_required(VERSION 3.15)
project(LearningOpenGL)

set(CMAKE_CXX_STANDARD 17)

add_executable(LearningOpenGL main.cpp)

find_package(glfw3 3.3 REQUIRED)
find_package(GLEW REQUIRED)
target_link_libraries(LearningOpenGL glfw3 GLEW::GLEW)
