#pragma once

#include "pch.h"

namespace opengl
{
    class Window
    {

    public:
        Window() = default;
        Window(int width, int height, const std::string &title);

        [[nodiscard]] inline auto getWindow() const { return window_; }
        [[nodiscard]] inline auto getWidth() const { return width_; }
        [[nodiscard]] inline auto getHeight() const { return height_; }
    private:
        GLFWwindow *window_ = nullptr;
        int width_, height_;
    };
}


