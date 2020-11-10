#pragma once

#include "pch.h"
#include "Camera.h"

namespace opengl
{
    class EventHandler
    {
    private:
        inline static std::shared_ptr<Camera> camera_ = std::make_shared<Camera>(glm::vec3(), glm::vec3(),
                                                                                 glm::vec3(), glm::mat4(1.0f));
        inline static MousePos mouse_pos_ {0, 0};
    private:
        static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void mouseCallback(GLFWwindow* window, double xpos, double ypos);
    public:
        static void init(GLFWwindow* window, const std::shared_ptr<Camera> &camera, MousePos mouse_pos);
    };
}

