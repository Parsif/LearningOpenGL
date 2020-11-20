#pragma once

#include "ecs/PhysicsSystem.h"
#include "Scene.h"

namespace opengl
{
    class EngineRenderer
    {
    public:
        EngineRenderer(Scene scene);

        void onUpdate();
        [[nodiscard]] auto getActiveCamera() const { return m_active_scene.getCamera(); }
    private:
        Scene m_active_scene;
        PhysicsSystem m_physics_system;
    };
}


