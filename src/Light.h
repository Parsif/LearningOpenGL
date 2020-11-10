#pragma once

#include "pch.h"

namespace opengl
{
    struct Light
    {
        glm::vec3 ambient, diffuse, specular;
    };

    struct DirLight : Light
    {
        glm::vec3 direction;
    };

    struct PointLight : Light
    {
        glm::vec3 position;
        float constant, linear, quadratic;
    };

    struct SpotLight : Light
    {
        glm::vec3 position, direction;
        float constant, linear, quadratic, cutoff;
    };
}
