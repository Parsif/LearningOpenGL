#include "EventHandler.h"

namespace opengl
{
    void EventHandler::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
    {
        if (action == GLFW_PRESS)
        {
            switch (key)
            {
                case GLFW_KEY_A:
                    camera_->translate(Direction::left);
                    break;
                case GLFW_KEY_S:
                    camera_->translate(Direction::down);
                    break;
                case GLFW_KEY_W:
                    camera_->translate(Direction::up);
                    break;
                case GLFW_KEY_D:
                    camera_->translate(Direction::right);
                    break;
                default: break;
            }
        }
    }


    void EventHandler::mouseCallback(GLFWwindow *window, double xpos, double ypos)
    {
        float xoffset = xpos - mouse_pos_.x;
        float yoffset = mouse_pos_.y - ypos;
        mouse_pos_.x = xpos;
        mouse_pos_.y = ypos;

        const float sensitivity = 0.1;
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        mouse_pos_.yaw += xoffset;
        mouse_pos_.pitch += yoffset;

        if(mouse_pos_.pitch > 89.0f)
            mouse_pos_.pitch = 89.0f;
        if(mouse_pos_.pitch < -89.0f)
            mouse_pos_.pitch = -89.0f;

        glm::vec3 front;
        front.x = cos(glm::radians(mouse_pos_.yaw)) * cos(glm::radians(mouse_pos_.pitch));
        front.y = sin(glm::radians(mouse_pos_.pitch));
        front.z = sin(glm::radians(mouse_pos_.yaw)) * cos(glm::radians(mouse_pos_.pitch));
        camera_->rotate(front);
    }

    void EventHandler::init(GLFWwindow *window, const std::shared_ptr<Camera> &camera, MousePos mouse_pos)
    {
        glfwSetKeyCallback(window, keyCallback);
        glfwSetCursorPosCallback(window, mouseCallback);
        camera_ = camera;
        mouse_pos_ = mouse_pos;
    }


}
