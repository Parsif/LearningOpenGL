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
                    camera_->move(Direction::left);
                    break;
                case GLFW_KEY_S:
                    camera_->move(Direction::down);
                    break;
                case GLFW_KEY_W:
                    camera_->move(Direction::up);
                    break;
                case GLFW_KEY_D:
                    camera_->move(Direction::right);
                    break;
                default: break;
            }
        }
    }

    void EventHandler::init(GLFWwindow *window, const std::shared_ptr<Camera> &camera)
    {
        glfwSetKeyCallback(window, keyCallback);
        camera_ = camera;
    }

}
