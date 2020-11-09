#include "Application.h"

#include "EventHandler.h"
#include "buffers/Buffer.h"
#include "model/Model.h"

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
        window_ = Window(1200, 800, "LearnOpenGL");
        if(glewInit() != GLEW_OK)
        {
            std::cout << "GLEW init failed\n";
            return;
        }

        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(messageCallback, nullptr);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

        mouse_pos_.x = window_.getWidth() / 2;
        mouse_pos_.y = window_.getHeight() / 2;
        glEnable(GL_DEPTH_TEST);

        glm::mat4 projection{1.0f};
        projection = glm::perspective(glm::radians(45.0f),
                                      static_cast<float>(window_.getWidth()) / window_.getHeight(),
                                      0.1f, 100.f);

        const auto camera = std::make_shared<Camera>(glm::vec3(0.f, 0.f, 3.f),
                            glm::vec3(0.f, 0.f, 0.f),
                              glm::vec3(0.f, 1.f, 0.f), projection);
        EventHandler::init(window_.getWindow(), camera, mouse_pos_);


        Model backpack("../res/backpack/backpack.obj");

        const Shader backpack_vertex_shader("../src/shaders/backpack_vertex.glsl", GL_VERTEX_SHADER);
        const Shader backpack_fragment_shader("../src/shaders/backpack_fragment.glsl", GL_FRAGMENT_SHADER);
        ShaderProgram backpack_sp({backpack_vertex_shader, backpack_fragment_shader});
        while (!glfwWindowShouldClose(window_.getWindow()))
        {                                                                                       
            glfwPollEvents();
            glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            backpack_sp.UseShaderProgram();
            backpack_sp.uniformMatrix4fv("projection", camera->getProjectionMatrix());
            backpack_sp.uniformMatrix4fv("view",  camera->getViewMatrix());
            // render the loaded model
            glm::mat4 model(1.0f);
            model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
            model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
            backpack_sp.uniformMatrix4fv("model", model);

            backpack.render(backpack_sp);
            glfwSwapBuffers(window_.getWindow());
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
