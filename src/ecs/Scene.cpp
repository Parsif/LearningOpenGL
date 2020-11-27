#include "Scene.h"

#include "renderer/Renderer3D.h"
#include "Components.h"

#include <glm/gtc/matrix_transform.hpp>

namespace opengl
{
    Scene::Scene(const Window& window)
    {
        glm::mat4 projection{1.0f};
        projection = glm::perspective(glm::radians(45.0f),
                                      static_cast<float>(window.getWidth()) / window.getHeight(),
                                      0.1f, 200.f);

        m_active_camera = std::make_shared<Camera>(glm::vec3(0.f, 0.f, 3.f),
                                            glm::vec3(0.f, 0.f, 0.f),
                                            glm::vec3(0.f, 1.f, 0.f), projection);

        m_model_library = ModelLibrary({"../res/backpack/backpack.obj", "../res/floor/floor.obj"});
    }

    void Scene::onUpdate()
    {
        auto group = m_registry.group<TransformComponent, ModelComponent>();
        auto view = m_registry.view<PointLightComponent>();

        auto& lighting_program = m_shader_library.getLightningProgram();
        lighting_program.useShaderProgram();
        for(auto entity: group) {
            for(auto entity1 : view)
            {
                Renderer3D::renderPointLight(view.get<PointLightComponent>(entity1), lighting_program);
            }
            auto [transform_comp, model_comp] = group.get<TransformComponent, ModelComponent>(entity);
            Renderer3D::renderModel(m_model_library.getModel(model_comp.model_path),
                                    transform_comp.getTransform(), m_active_camera->getViewProjection(),
                                    m_active_camera->getGetPosition(), lighting_program);
        }


    }


}
