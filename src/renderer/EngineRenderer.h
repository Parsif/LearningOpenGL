#ifndef LEARNINGOPENGL_ENGINERENDERER_H
#define LEARNINGOPENGL_ENGINERENDERER_H

#include "Scene.h"

#include <vector>

namespace opengl
{
    class EngineRenderer
    {
    public:
        EngineRenderer(std::vector<Scene> scenes);

        void render();
    private:
        std::vector<Scene> m_scenes
    };
}




#endif //LEARNINGOPENGL_ENGINERENDERER_H
