#ifndef LEARNINGOPENGL_EVENTHANDLER_H
#define LEARNINGOPENGL_EVENTHANDLER_H

#include <GLFW/glfw3.h>
#include "Camera.h"

namespace opengl
{
    class EventHandler
    {
    private:
        static Camera camera_;
    private:
        static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    public:
        static void init(GLFWwindow* window, const Camera& camera);
    };
}



#endif //LEARNINGOPENGL_EVENTHANDLER_H
