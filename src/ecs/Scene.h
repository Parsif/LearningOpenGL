#pragma once

#include <entt/entt.h>
#include "ModelLibrary.h"
#include "Window.h"
#include "Camera.h"

namespace opengl
{
    class Scene
    {
    public:
        explicit Scene(const Window& window);
        void onUpdate();

        template<class T>
        void addComponent(entt::entity entity)
        {
            m_registry.insert<T>(entity);
        }

        [[nodiscard]] inline auto& getActiveCamera() const { return m_active_camera; }
    private:
        std::shared_ptr<Camera> m_active_camera;
        entt::registry m_registry;
        ModelLibrary m_model_library;
    };
}




