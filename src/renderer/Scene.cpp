#include "Scene.h"

#include <utility>


namespace opengl
{

    Scene::Scene(std::vector<Entity>  entities, const Window& window) : m_entities(std::move(entities))
    {
        glm::mat4 projection{1.0f};
        projection = glm::perspective(glm::radians(45.0f),
                                      static_cast<float>(window.getWidth()) / window.getHeight(),
                                      0.1f, 100.f);

        m_camera = Camera(glm::vec3(0.f, 0.f, 3.f),
                          glm::vec3(0.f, 0.f, 0.f),
                          glm::vec3(0.f, 1.f, 0.f), projection);
    }

    void Scene::addEntity(Entity entity)
    {
        m_entities.emplace_back(std::move(entity));
    }

    void Scene::render()
    {
        for (auto&& entity : m_entities) {
            entity.render(m_camera.value());
        }
    }


}