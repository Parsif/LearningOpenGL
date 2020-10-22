#ifndef LEARNINGOPENGL_LIGHT_H
#define LEARNINGOPENGL_LIGHT_H

#include <glm/glm.hpp>
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

#endif //LEARNINGOPENGL_LIGHT_H
