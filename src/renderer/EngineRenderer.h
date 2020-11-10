#pragma once

#include "Scene.h"

namespace opengl
{
    class EngineRenderer
    {
    public:
        EngineRenderer(Scene scene);

        void render();
    private:
        Scene m_active_scene;
    };
}


