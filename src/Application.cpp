#include "Application.h"

#include "EventHandler.h"
#include "buffers/VertexBuffer.h"
#include "drawable/Lamp.h"
#include "drawable/Cube.h"
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
        const auto window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
        if (window == nullptr)
        {
            std::cout << "GLFW Window creation failed\n";
            glfwTerminate();
            return;
        }

        glfwMakeContextCurrent(window);
        if(glewInit() != GLEW_OK)
        {
            std::cout << "GLEW init failed\n";
            return;
        }

        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(messageCallback, nullptr);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

        glfwGetFramebufferSize(window, &window_width_, &window_height_);
        glViewport(0, 0, window_width_, window_height_);
        mouse_pos_.x = window_width_ / 2;
        mouse_pos_.y = window_height_ / 2;
        projection_ = glm::perspective(glm::radians(45.f), static_cast<float>(window_width_) / window_height_, 0.1f, 100.f);
        glEnable(GL_DEPTH_TEST);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        EventHandler::init(window, camera_, mouse_pos_);

        Model backpack("../res/backpack/backpack.obj");

        const Shader backpack_vertex_shader("../src/shaders/backpack_vertex.glsl", GL_VERTEX_SHADER);
        const Shader backpack_fragment_shader("../src/shaders/backpack_fragment.glsl", GL_FRAGMENT_SHADER);
        ShaderProgram backpack_sp({backpack_vertex_shader, backpack_fragment_shader});
        while (!glfwWindowShouldClose(window))
        {                                                                                       
            glfwPollEvents();
            glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            backpack_sp.UseShaderProgram();

            glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)window_width_ / (float)window_height_, 0.1f, 100.0f);
            backpack_sp.uniformMatrix4fv("projection", projection);
            backpack_sp.uniformMatrix4fv("view",  camera_->getViewMatrix());

            // render the loaded model
            glm::mat4 model(1.0f);
            model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
            model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
            backpack_sp.uniformMatrix4fv("model", model);

            backpack.render(backpack_sp);
            glfwSwapBuffers(window);
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
