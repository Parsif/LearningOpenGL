#ifndef LEARNINGOPENGL_APPLICATION_H
#define LEARNINGOPENGL_APPLICATION_H

#include "Shader.h"

namespace opengl
{
    class Application
    {
    private:

    public:
        Application();
        ~Application();
        Application operator=(const Application&) = delete;
        Application(const Application&) = delete;

        void Run();
    };
}


#endif //LEARNINGOPENGL_APPLICATION_H
