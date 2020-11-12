#pragma once

#include "Scene.h"

namespace opengl
{
    class EngineRenderer
    {
    public:
        EngineRenderer(Scene scene);

        void render();
        [[nodiscard]] auto getActiveCamera() const { return m_active_scene.getCamera(); }
    private:
        Scene m_active_scene;
    };
}


