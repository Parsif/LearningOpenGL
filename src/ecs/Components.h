#pragma once

#include "pch.h"

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>

namespace opengl
{
    struct TagComponent
    {
        TagComponent(std::string tag) : tag_name(std::move(tag)){}
        std::string tag_name;
    };

    struct TransformComponent
    {
        TransformComponent(glm::vec3 translation, glm::vec3 rotation, glm::vec3 scale)
        : translation(translation), rotation(rotation) ,scale(scale) {}
        TransformComponent(glm::vec3 translation) : translation(translation) {}
        TransformComponent() = default;
        glm::vec3 translation{0.0f}, rotation{0.0f}, scale{1.0f};

        [[nodiscard]] inline auto getTransform() const
        {
            glm::mat4 transform(1.0f);
            transform = glm::translate(transform, translation);
            transform = glm::rotate(transform, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
            transform = glm::rotate(transform, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
            transform = glm::rotate(transform, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
            transform = glm::scale(transform, scale);

            return transform;
        }
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