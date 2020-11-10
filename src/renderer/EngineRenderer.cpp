#include "EngineRenderer.h"


namespace opengl
{
    EngineRenderer::EngineRenderer(std::vector<Scene> scenes) : m_scenes(std::move(scenes))
    {

    }

    void EngineRenderer::render()
    {
        for(auto&& scene : m_scenes) {
            scene.render();
        }
    }
}


