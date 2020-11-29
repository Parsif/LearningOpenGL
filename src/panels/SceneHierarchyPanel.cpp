#include "SceneHierarchyPanel.h"

#include <glm/gtc/type_ptr.hpp>

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
        if(ImGui::BeginPopupContextWindow(0, 1, false))
        {
            if (ImGui::MenuItem("Create empty entity"))
                m_scene->createEntity("Empty entity");

            ImGui::EndPopup();
        }

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


        bool entityDeleted = false;
        if (ImGui::BeginPopupContextItem())
        {
            if (ImGui::MenuItem("Delete entity"))
                entityDeleted = true;

            ImGui::EndPopup();
        }

        if(opened)
        {
            ImGui::TreePop();
        }

        if (entityDeleted)
        {
            if(entity == m_selected_entity)
                m_selected_entity = {};
            m_scene->deleteComponent(entity);
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
            auto& transform_component = m_scene->m_registry.get<TransformComponent>(entity);

            if(ImGui::TreeNodeEx((void*)typeid(TransformComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Transform"))
            {
                ImGui::DragFloat3("Position", glm::value_ptr(transform_component.translation), 0.1f);
                ImGui::DragFloat3("Rotation", glm::value_ptr(transform_component.rotation), 0.1f);
                ImGui::DragFloat3("Scale", glm::value_ptr(transform_component.scale), 0.1f);

                ImGui::TreePop();
            }
        }

        if(m_scene->m_registry.has<PointLightComponent>(entity))
        {
            if(ImGui::TreeNodeEx((void*)typeid(PointLightComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Point light"))
            {
                auto &point_light_component = m_scene->m_registry.get<PointLightComponent>(entity);
                ImGui::DragFloat3("Position", glm::value_ptr(point_light_component.position), 0.1f);
                ImGui::DragFloat3("Albedo", glm::value_ptr(point_light_component.albedo), 0.1f);
                ImGui::DragFloat("Constant", &point_light_component.constant, 0.01f);
                ImGui::DragFloat("Linear", &point_light_component.linear, 0.01f);
                ImGui::DragFloat("Quadratic", &point_light_component.quadratic, 0.01f);

                ImGui::TreePop();
            }
        }
    }
}