#include "EngineRenderer.h"

#include <utility>


namespace opengl
{
    EngineRenderer::EngineRenderer(Scene scene) : m_active_scene(std::move(scene))
    {

    }

    void EngineRenderer::onUpdate()
    {
       m_active_scene.render();
    }
}


