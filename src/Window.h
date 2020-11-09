#ifndef LEARNINGOPENGL_WINDOW_H
#define LEARNINGOPENGL_WINDOW_H

#include <string>

#include <GLFW/glfw3.h>

namespace opengl
{
    class Window
    {
    private:
        GLFWwindow *window_ = nullptr;
        int width_, height_;
    public:
        Window() = default;
        Window(int width, int height, const std::string &title);

        [[nodiscard]] inline auto getWindow() const { return window_; }
        [[nodiscard]] inline auto getWidth() const { return width_; }
        [[nodiscard]] inline auto getHeight() const { return height_; }
    };
}



#endif //LEARNINGOPENGL_WINDOW_H
