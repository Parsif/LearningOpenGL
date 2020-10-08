#ifndef LEARNINGOPENGL_EVENTHANDLER_H
#define LEARNINGOPENGL_EVENTHANDLER_H

#include <GLFW/glfw3.h>
#include "Camera.h"

#include <memory>

namespace opengl
{
    class EventHandler
    {
    private:
        inline static std::shared_ptr<Camera> camera_ = std::make_shared<Camera>(glm::vec3(), glm::vec3(), glm::vec3());
    private:
        static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    public:
        static void init(GLFWwindow* window, const std::shared_ptr<Camera> &camera);
    };
}



#endif //LEARNINGOPENGL_EVENTHANDLER_H
