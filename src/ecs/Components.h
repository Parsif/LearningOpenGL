#pragma once

#include "pch.h"
#include <glm/glm.hpp>

namespace opengl
{
    using EntityIdType = uint32_t;

    struct Component {};

    struct TransformComponent : Component
    {
        glm::vec3 position;
        glm::vec3 scale;
        glm::vec3 rotation;
    };

    struct PointLightComponent : Component
    {
        glm::vec3 position;
        float constant, linear, quadratic;
        std::string uniform_name;
    };

    template <typename Type>
    using ComponentMapType = std::unordered_map<EntityIdType, Type>;
}