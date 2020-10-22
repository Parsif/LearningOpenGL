#ifndef LEARNINGOPENGL_APPLICATION_H
#define LEARNINGOPENGL_APPLICATION_H

#include "Shader.h"
#include "Camera.h"
#include "ShaderProgram.h"
#include "buffers/VertexArray.h"

#include "global.h"
#include "Texture.h"

#include <memory>

namespace opengl
{
    class Application
    {
    private:
        MousePos mouse_pos_;
        int window_width_, window_height_;
        std::shared_ptr<Camera> camera_ = std::make_shared<Camera>(glm::vec3(0.f, 0.f, 3.f),
                                   glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));
        glm::mat4 projection_{1.0f};

    private:
        static void messageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, GLchar const* message, void const* user_param);
    public:
        Application();
        ~Application();
        Application operator=(const Application&) = delete;
        Application(const Application&) = delete;

        void Run();
    };
}


#endif //LEARNINGOPENGL_APPLICATION_H
