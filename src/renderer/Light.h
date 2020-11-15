#pragma once

#include "pch.h"
#include "Entity.h"

namespace opengl
{
    class Light : public Entity
    {
    public:
        glm::vec3 ambient, diffuse, specular;
    };

    class DirectionLight : Light
    {
        glm::vec3 direction;
    };

    class PointLight : Light
    {
        glm::vec3 position;
        float constant, linear, quadratic;
    };

    class SpotLight : Light
    {
        glm::vec3 position, direction;
        float constant, linear, quadratic, cutoff;
    };
}
