cmake_minimum_required(VERSION 3.16)
project(LearningOpenGL)

set(CMAKE_CXX_STANDARD 17)

add_executable(LearningOpenGL
        #vendor
        vendor/imgui/imgui_draw.cpp vendor/imgui/imgui.cpp vendor/imgui/imgui_demo.cpp vendor/imgui/imgui_impl_glfw.cpp
        vendor/imgui/imgui_impl_opengl3.cpp vendor/imgui/imgui_widgets.cpp
        vendor/std_image.h vendor/stb_image.cpp
        src/main.cpp src/Shader.cpp src/Shader.h src/Application.cpp src/Application.h
        src/ShaderProgram.cpp src/ShaderProgram.h src/FileTexture.cpp src/FileTexture.h
        src/Camera.cpp src/buffers/VertexArray.cpp src/EventHandler.cpp src/EventHandler.h src/global.h
        src/model/Mesh.cpp src/model/Mesh.h src/model/Model.cpp src/model/Model.h src/buffers/Buffer.cpp src/buffers/Buffer.h
        src/Window.cpp src/Window.h src/renderer/EngineRenderer.cpp src/renderer/EngineRenderer.h src/renderer/SceneObject.cpp
        src/renderer/SceneObject.h src/renderer/Scene.cpp src/layers/Layer.h src/pch.h src/layers/ImGuiLayer.cpp src/layers/ImGuiLayer.h src/renderer/Light.h src/buffers/FrameBuffer.cpp src/buffers/FrameBuffer.h src/types.h src/ecs/Components.h src/ecs/PhysicsSystem.cpp src/ecs/PhysicsSystem.h src/ShaderLibrary.cpp src/ShaderLibrary.h src/ecs/ComponentManager.h src/ecs/EntityManager.h)


target_include_directories(LearningOpenGL PRIVATE vendor src)

find_package(glfw3 3.3 REQUIRED)
find_package(GLEW REQUIRED)
target_link_libraries(LearningOpenGL glfw3 GLEW::GLEW assimp)

target_precompile_headers(LearningOpenGL PRIVATE src/pch.h)
