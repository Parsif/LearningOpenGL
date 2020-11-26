#pragma once

#include "pch.h"

#include "Shader.h"
#include "Camera.h"
#include "ShaderProgram.h"
#include "buffers/VertexArray.h"

#include "global.h"
#include "FileTexture.h"
#include "Window.h"

#include "ecs/Scene.h"

#include "layers/ImGuiLayer.h"


namespace opengl
{
    class Application
    {
    public:
        Application();
        ~Application();
        Application operator=(const Application&) = delete;
        Application(const Application&) = delete;

        void run();
        [[nodiscard]] inline auto& getWindow() const { return m_window; }

        [[nodiscard]] static inline auto& getInstance() { return *s_instance; }

    private:
        Window m_window;
        ImGuiLayer m_ImGuiLayer;
        std::shared_ptr<Scene> m_active_scene;
        static Application* s_instance;

    private:
        static void messageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, GLchar const* message, void const* user_param);
    };
}

