#ifndef LEARNINGOPENGL_RENDERER_H
#define LEARNINGOPENGL_RENDERER_H

#include "Scene.h"


#include <GLFW/glfw3.h>
#include <imgui/ImGuiFileBrowser.h>


namespace opengl
{
    class Renderer
    {
    private:
        static void renderScene(const Scene &scene);
        static void renderMenu();
        static void renderModelInfo(const Model &model);
    public:
        static void init(GLFWwindow *window);
        static void render(const Scene &scene);
    };
}



#endif //LEARNINGOPENGL_RENDERER_H
