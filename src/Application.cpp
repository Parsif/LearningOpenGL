#include "Application.h"

#include "EventHandler.h"
#include "buffers/Buffer.h"
#include "model/Model.h"
#include "renderer/EngineRenderer.h"

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

namespace opengl
{

    Application::Application()
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    }

    Application::~Application()
    {
        glfwTerminate();
    }

    void Application::Run()
    {
        m_window = Window(1200, 800, "LearnOpenGL");
        if(glewInit() != GLEW_OK)
        {
            std::cout << "GLEW init failed\n";
            return;
        }

        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(messageCallback, nullptr);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

        mouse_pos_.x = m_window.getWidth() / 2;
        mouse_pos_.y = m_window.getHeight() / 2;
        glEnable(GL_DEPTH_TEST);

        glm::mat4 projection{1.0f};
        projection = glm::perspective(glm::radians(45.0f),
                                      static_cast<float>(m_window.getWidth()) / m_window.getHeight(),
                                      0.1f, 100.f);

        const auto camera = std::make_shared<Camera>(glm::vec3(0.f, 0.f, 3.f),
                            glm::vec3(0.f, 0.f, 0.f),
                              glm::vec3(0.f, 1.f, 0.f), projection);
        EventHandler::init(m_window.getWindow(), camera, mouse_pos_);

       // Model backpack("../res/backpack/backpack.obj");

        const Shader backpack_vertex_shader("../src/shaders/backpack_vertex.glsl", GL_VERTEX_SHADER);
        const Shader backpack_fragment_shader("../src/shaders/backpack_fragment.glsl", GL_FRAGMENT_SHADER);
        ShaderProgram backpack_sp({backpack_vertex_shader, backpack_fragment_shader});
        EngineRenderer engine_renderer({
            Scene(
                {Entity("../res/backpack/backpack.obj", backpack_sp)}, m_window)
        });



        while (!glfwWindowShouldClose(m_window.getWindow()))
        {                                                                                       
            glfwPollEvents();
            glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            engine_renderer.render();
            glfwSwapBuffers(m_window.getWindow());
        }
    }

    void Application::messageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                                      const GLchar *message, const void *user_param)
    {
        auto source_str = [source]() -> std::string {
            switch (source)
            {
                case GL_DEBUG_SOURCE_API: return "API";
                case GL_DEBUG_SOURCE_WINDOW_SYSTEM: return "WINDOW SYSTEM";
                case GL_DEBUG_SOURCE_SHADER_COMPILER: return "SHADER COMPILER";
                case GL_DEBUG_SOURCE_THIRD_PARTY:  return "THIRD PARTY";
                case GL_DEBUG_SOURCE_APPLICATION: return "APPLICATION";
                case GL_DEBUG_SOURCE_OTHER: return "OTHER";
                default: return "UNKNOWN";
            }
        }();

        auto type_str = [type]() {
            switch (type)
            {
                case GL_DEBUG_TYPE_ERROR: return "ERROR";
                case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: return "DEPRECATED_BEHAVIOR";
                case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: return "UNDEFINED_BEHAVIOR";
                case GL_DEBUG_TYPE_PORTABILITY: return "PORTABILITY";
                case GL_DEBUG_TYPE_PERFORMANCE: return "PERFORMANCE";
                case GL_DEBUG_TYPE_MARKER:  return "MARKER";
                case GL_DEBUG_TYPE_OTHER: return "OTHER";
                default: return "UNKNOWN";
            }
        }();

        auto severity_str = [severity]() {
            switch (severity) {
                case GL_DEBUG_SEVERITY_NOTIFICATION: return "NOTIFICATION";
                case GL_DEBUG_SEVERITY_LOW: return "LOW";
                case GL_DEBUG_SEVERITY_MEDIUM: return "MEDIUM";
                case GL_DEBUG_SEVERITY_HIGH: return "HIGH";
                default: return "UNKNOWN";
            }
        }();

        std::cout << source_str   << ", "
                  << type_str     << ", "
                  << severity_str << ", "
                  << id           << ": "
                  << message      << '\n';
    }

}
