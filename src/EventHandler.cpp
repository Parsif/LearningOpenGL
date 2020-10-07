#include "EventHandler.h"

namespace opengl
{
    void EventHandler::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
    {
        const float kcameraSpeed = 0.3f;
        if (action == GLFW_PRESS)
        {
            switch (key)
            {
                case GLFW_KEY_A:
                    break;
                case GLFW_KEY_S:
                    break;
                case GLFW_KEY_W:
                    break;
                case GLFW_KEY_D:
                    break;
                default: break;
            }
        }
    }

    void EventHandler::init(GLFWwindow *window, const Camera &camera)
    {
        glfwSetKeyCallback(window, keyCallback);
        camera_ = camera;
    }

}
