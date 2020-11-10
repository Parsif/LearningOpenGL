#pragma once

#include "pch.h"

#include "Window.h"
#include "Camera.h"
#include "Entity.h"


namespace opengl
{
    class Scene
    {
    public:
        Scene(std::vector<Entity> entities, const Window& window);

        void render();
        void addEntity(Entity entity);
        [[nodiscard]] inline auto&& getEntities() const { return m_entities; };

    private:
        std::vector<Entity> m_entities;
        std::optional<Camera> m_camera;
    };
}

