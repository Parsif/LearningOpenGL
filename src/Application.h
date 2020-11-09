#ifndef LEARNINGOPENGL_APPLICATION_H
#define LEARNINGOPENGL_APPLICATION_H

#include "Shader.h"
#include "Camera.h"
#include "ShaderProgram.h"
#include "buffers/VertexArray.h"

#include "global.h"
#include "FileTexture.h"
#include "Window.h"

namespace opengl
{
    class Application
    {
    private:
        MousePos mouse_pos_;
        Window window_;


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
