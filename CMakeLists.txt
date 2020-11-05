cmake_minimum_required(VERSION 3.15)
project(LearningOpenGL)

set(CMAKE_CXX_STANDARD 17)

add_executable(LearningOpenGL src/main.cpp src/Shader.cpp src/Shader.h src/Application.cpp src/Application.h
            src/ShaderProgram.cpp src/ShaderProgram.h src/FileTexture.cpp src/FileTexture.h vendor/std_image.h vendor/stb_image.cpp
            src/Camera.cpp src/buffers/IndexBuffer.cpp src/buffers/VertexArray.cpp src/buffers/VertexBuffer.cpp src/EventHandler.cpp
            src/EventHandler.h src/global.h src/Light.h src/model/Mesh.cpp src/model/Mesh.h src/model/Model.cpp src/model/Model.h
            src/imgui/imgui_impl_glfw.cpp src/imgui/imgui_impl_opengl3.cpp src/Scene.cpp src/Scene.h src/imgui/imgui.cpp src/imgui/imgui_widgets.cpp
            src/imgui/imgui_draw.cpp src/imgui/imgui_demo.cpp src/imgui/ImGuiFileBrowser.cpp  src/Renderer.cpp src/Renderer.h)

target_include_directories(LearningOpenGL PRIVATE vendor src)

find_package(glfw3 3.3 REQUIRED)
find_package(GLEW REQUIRED)
target_link_libraries(LearningOpenGL glfw3 GLEW::GLEW assimp)
