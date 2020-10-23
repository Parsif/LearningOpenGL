cmake_minimum_required(VERSION 3.15)
project(LearningOpenGL)

set(CMAKE_CXX_STANDARD 17)

add_executable(LearningOpenGL src/main.cpp src/Shader.cpp src/Shader.h src/Application.cpp src/Application.h
        src/ShaderProgram.cpp src/ShaderProgram.h src/Texture.cpp src/Texture.h vendor/std_image.h vendor/stb_image.cpp
        src/Camera.cpp src/buffers/IndexBuffer.cpp src/buffers/VertexArray.cpp src/buffers/VertexBuffer.cpp src/EventHandler.cpp src/EventHandler.h src/global.h src/drawable/Lamp.cpp src/drawable/Lamp.h src/materials.h src/drawable/Cube.cpp src/drawable/Cube.h src/Light.h src/Mesh.cpp src/Mesh.h)

target_include_directories(LearningOpenGL PRIVATE vendor src)

find_package(glfw3 3.3 REQUIRED)
find_package(GLEW REQUIRED)
target_link_libraries(LearningOpenGL glfw3 GLEW::GLEW assimp)
