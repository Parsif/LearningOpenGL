#pragma once

#include "pch.h"
#include <glm/glm.hpp>

namespace opengl
{
    struct TransformComponent
    {
        glm::mat4 transform{1.0f};
    };

    struct ModelComponent
    {
        std::string model_path;
    };

    struct PointLightComponent
    {
        glm::vec3 position;
        float constant, linear, quadratic;
    };
}