#include "Scene.h"
namespace opengl
{

    void Scene::addModel(Model model)
    {
        models_.emplace_back(std::move(model));
    }
}