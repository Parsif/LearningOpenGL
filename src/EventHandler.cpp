#include "EventHandler.h"

namespace opengl
{
    void EventHandler::mouseCallback(GLFWwindow *window, double xpos, double ypos)
    {
        float xoffset = xpos - m_mouse_pos.x;
        float yoffset = m_mouse_pos.y - ypos;
        m_mouse_pos.x = xpos;
        m_mouse_pos.y = ypos;

        const float sensitivity = 0.1;
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        m_mouse_pos.yaw += xoffset;
        m_mouse_pos.pitch += yoffset;

        if(m_mouse_pos.pitch > 89.0f)
            m_mouse_pos.pitch = 89.0f;
        if(m_mouse_pos.pitch < -89.0f)
            m_mouse_pos.pitch = -89.0f;

        glm::vec3 front;
        front.x = cos(glm::radians(m_mouse_pos.yaw)) * cos(glm::radians(m_mouse_pos.pitch));
        front.y = sin(glm::radians(m_mouse_pos.pitch));
        front.z = sin(glm::radians(m_mouse_pos.yaw)) * cos(glm::radians(m_mouse_pos.pitch));
        m_camera->rotate(front);
    }

    void EventHandler::init(GLFWwindow *window, const std::shared_ptr<Camera> &camera, const glm::vec2& mouse_pos)
    {
        glfwSetCursorPosCallback(window, mouseCallback);
        m_camera = camera;
        m_mouse_pos.x = mouse_pos.x;
        m_mouse_pos.y = mouse_pos.y;
    }

    void EventHandler::processInput(GLFWwindow *window)
    {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            m_camera->translate(Direction::Up);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            m_camera->translate(Direction::Down);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            m_camera->translate(Direction::Left);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            m_camera->translate(Direction::Right);
    }


}
