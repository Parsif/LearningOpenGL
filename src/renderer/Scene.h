#pragma once

#include "pch.h"

#include "Window.h"
#include "Camera.h"
#include "SceneObject.h"


namespace opengl
{
    class Scene
    {
    public:
        Scene(std::vector<Entity> entities, const Window& window);

        void render();
        void addEntity(Entity entity);
        [[nodiscard]] inline auto getCamera() const { return m_camera; };

    private:
        std::vector<Entity> m_entities;
        std::shared_ptr<Camera> m_camera;
    };
}
