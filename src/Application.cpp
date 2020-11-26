#include "Application.h"
#include "EventHandler.h"

namespace opengl
{
    Application* Application::s_instance = nullptr;
    Application::Application()
    {
        s_instance = this;
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

    void Application::run()
    {
        m_window = Window(1200, 800, "LearnOpenGL");
        if(glewInit() != GLEW_OK)
        {
            std::cout << "GLEW init failed\n";
            return;
        }

        m_active_scene = std::make_shared<Scene>(m_window);
        m_ImGuiLayer = ImGuiLayer(m_active_scene);
        auto backpack_e = m_active_scene->createEntity("Backpack");
        m_active_scene->addComponent<TransformComponent>(backpack_e);
        m_active_scene->addComponent<ModelComponent>(backpack_e, "../res/backpack/backpack.obj");

        auto floor_entity = m_active_scene->createEntity("Floor");
        m_active_scene->addComponent<TransformComponent>(floor_entity);
        m_active_scene->addComponent<ModelComponent>(floor_entity, "../res/floor/floor.obj");

        auto point_light_e = m_active_scene->createEntity("Point light");
        m_active_scene->addComponent<PointLightComponent>(point_light_e, glm::vec3(1.0f, 0.9f, 0.1f), glm::vec3(0.7f), glm::vec3(0.7f),
                                                glm::vec3(0.0f, 4.0f, 0.0f),
                                                1.0f, 0.09f, 0.032f);

        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(messageCallback, nullptr);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glEnable(GL_DEPTH_TEST);

        EventHandler::init(m_window.getGLFWwindow(), m_active_scene->getActiveCamera(),
                           glm::vec2( m_window.getWidth() / 2, m_window.getHeight() / 2));

        m_ImGuiLayer.onAttach();

        FrameBufferSpecifications specifications;
        specifications.width = m_window.getWidth();
        specifications.height = m_window.getHeight();
        FrameBuffer frame_buffer(specifications);

        while (!glfwWindowShouldClose(m_window.getGLFWwindow()))
        {
            frame_buffer.bind();
            glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            m_active_scene->onUpdate();
            frame_buffer.unbind();

            m_ImGuiLayer.begin();
            m_ImGuiLayer.onImGuiRender(frame_buffer);
            m_ImGuiLayer.end();

            EventHandler::processInput(m_window.getGLFWwindow());
            glfwSwapBuffers(m_window.getGLFWwindow());
            glfwPollEvents();
        }
    }

    void Application::messageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                                      const GLchar *message, const void *user_param)
    {
        if(severity == GL_DEBUG_SEVERITY_NOTIFICATION) return;

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
