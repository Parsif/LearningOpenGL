#pragma once

#include "pch.h"
#include <glm/glm.hpp>

namespace opengl
{
    struct TagComponent
    {
        TagComponent(std::string tag) : tag_name(std::move(tag)){}
        std::string tag_name;
    };

    struct TransformComponent
    {
        TransformComponent(const glm::mat4& trans) : transform(trans){}
        TransformComponent() = default;
        glm::mat4 transform{1.0f};
    };

    struct ModelComponent
    {
        ModelComponent(std::string path) : model_path(std::move(path)){}
        std::string model_path;
    };

    struct PointLightComponent
    {
        PointLightComponent(const glm::vec3& position,  glm::vec3 ambient,  glm::vec3 diffuse, glm::vec3 specular,
                            float constant, float linear, float quadratic)
                : position(position), ambient(ambient),  diffuse(diffuse), specular(specular),
                  constant(constant), linear(linear), quadratic(quadratic)
        {}
        PointLightComponent() = default;
        glm::vec3 position;
        glm::vec3 ambient, diffuse, specular;
        float constant, linear, quadratic;
    };
}