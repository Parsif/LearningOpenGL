#ifndef LEARNINGOPENGL_APPLICATION_H
#define LEARNINGOPENGL_APPLICATION_H

#include "Shader.h"
#include "Camera.h"

#include <memory>

namespace opengl
{
    class Application
    {
    private:
        std::shared_ptr<Camera> camera_ = std::make_shared<Camera>(glm::vec3(0.f, 0.f, 3.f),
                                   glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));
    public:
        Application();
        ~Application();
        Application operator=(const Application&) = delete;
        Application(const Application&) = delete;

        void Run();
    };
}


#endif //LEARNINGOPENGL_APPLICATION_H
