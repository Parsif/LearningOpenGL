#pragma once

#include "ecs/Scene.h"

namespace opengl
{
    class SceneHierarchyPanel
    {
    public:
        SceneHierarchyPanel() = default;
        SceneHierarchyPanel(const std::shared_ptr<Scene>& scene);
        void onImGuiRender();

    private:
        void drawEntityNode(entt::entity entity);

    private:
        std::shared_ptr<Scene> m_scene;
        entt::entity m_selected_entity;
    };
}




