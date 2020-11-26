#pragma once

#include <entt/entt.h>
#include "ShaderLibrary.h"
#include "ModelLibrary.h"
#include "Window.h"
#include "Camera.h"
#include "Components.h"

namespace opengl
{
    class Scene
    {
    public:
        explicit Scene(const Window& window);
        void onUpdate();

        [[nodiscard]] inline auto createEntity(const std::string& tag_name)
        {
            auto entity = m_registry.create();
            addComponent<TagComponent>(entity, tag_name);
            return entity;
        }

        template<class T, class... Args>
        T& addComponent(entt::entity entity, Args&&... args)
        {
            return m_registry.emplace<T>(entity, std::forward<Args>(args)...);
        }

        [[nodiscard]] inline auto& getActiveCamera() const { return m_active_camera; }

    private:
        std::shared_ptr<Camera> m_active_camera;
        entt::registry m_registry;
        ModelLibrary m_model_library;
        ShaderLibrary m_shader_library;


        friend class SceneHierarchyPanel;
    };
}




