#include "Window.h"

namespace opengl
{
    Window::Window(int width, int height, const std::string &title) : width_(width), height_(height)
    {
        window_ = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

        if (window_ == nullptr)
        {
            std::cerr << "GLFW Window creation failed\n";
            glfwTerminate();
            return;
        }

        glfwMakeContextCurrent(window_);
        glfwGetFramebufferSize(window_, &width_, &height_);
        glViewport(0, 0, width_, height_);
       // glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
}

