#include "Scene.h"


#include <glm/gtc/matrix_transform.hpp>

namespace opengl
{

    Scene::Scene(std::vector<SceneObject> scene_objects, std::vector<PointLight> lights, const Window& window)
    : m_scene_objects(std::move(scene_objects)), m_lights(std::move(lights))
    {
        glm::mat4 projection{1.0f};
        projection = glm::perspective(glm::radians(45.0f),
                                      static_cast<float>(window.getWidth()) / window.getHeight(),
                                      0.1f, 200.f);

        m_camera = std::make_shared<Camera>(glm::vec3(0.f, 0.f, 3.f),
                          glm::vec3(0.f, 0.f, 0.f),
                          glm::vec3(0.f, 1.f, 0.f), projection);
    }

    void Scene::render()
    {
        for (auto&& objects : m_scene_objects) {
            objects.render(*m_camera, m_lights[0]);
        }
    }


}