#pragma once

#include "pch.h"
#include "Camera.h"

namespace opengl
{
    struct MousePos
    {
        float x{}, y{}, pitch = 0.f, yaw = -90.0f;
    };

    class EventHandler
    {
    public:
        static void init(GLFWwindow* window, const std::shared_ptr<Camera> &camera, const glm::vec2& mouse_pos);
        static void processInput(GLFWwindow* window);
    private:
        inline static std::shared_ptr<Camera> m_camera = std::make_shared<Camera>(glm::vec3(), glm::vec3(),
                                                                                  glm::vec3(), glm::mat4(1.0f));
        inline static MousePos m_mouse_pos {0, 0};
    private:
        static void mouseCallback(GLFWwindow* window, double xpos, double ypos);
    };
}

