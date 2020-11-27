#include "SceneHierarchyPanel.h"

#include <imgui/imgui.h>

namespace opengl
{
    SceneHierarchyPanel::SceneHierarchyPanel(const std::shared_ptr<Scene>& scene) : m_scene(scene)
    {
    }

    void SceneHierarchyPanel::onImGuiRender()
    {
        ImGui::Begin("Scene hierarchy");
        m_scene->m_registry.each([&](auto entity)
        {
            drawEntityNode(entity);
        });
        ImGui::End();
        ImGui::Begin("Properties");
        drawEntityProperties(m_selected_entity);
        ImGui::End();
    }

    void SceneHierarchyPanel::drawEntityNode(entt::entity entity)
    {
        const auto& tag = m_scene->m_registry.get<TagComponent>(entity).tag_name;
        ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow |
                (m_selected_entity == entity ? ImGuiTreeNodeFlags_Selected : 0);
        bool opened = ImGui::TreeNodeEx((void*)entity, flags, tag.c_str());
        if(ImGui::IsItemClicked())
        {
            m_selected_entity = entity;
        }
        if(opened)
        {
            ImGui::TreePop();
        }
    }

    void SceneHierarchyPanel::drawEntityProperties(entt::entity entity)
    {
        if(m_scene->m_registry.has<TagComponent>(entity))
        {
            auto& tag = m_scene->m_registry.get<TagComponent>(entity).tag_name;
            char buffer[256];
            memset(buffer, 0, sizeof(buffer));
            strcpy_s(buffer, sizeof(buffer), tag.c_str());
            if(ImGui::InputText("Tag", buffer, sizeof(buffer)))
            {
                tag = std::string(buffer);
            }
        }

        if(m_scene->m_registry.has<TransformComponent>(entity))
        {
//            ImGui::DragFloat3()
        }
    }
}