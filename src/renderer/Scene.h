#pragma once

#include "pch.h"

#include "Window.h"
#include "Camera.h"
#include "SceneObject.h"
#include "Light.h"


namespace opengl
{
    class Scene
    {
    public:
        Scene(std::vector<SceneObject> scene_objects, std::vector<PointLight> lights, const Window& window);

        void render();
        [[nodiscard]] inline auto getCamera() const { return m_camera; };

    private:
        std::vector<SceneObject> m_scene_objects;
        std::vector<PointLight> m_lights;
        std::shared_ptr<Camera> m_camera;
    };
}

