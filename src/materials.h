//
// Created by Владислав on 09.10.2020.
//

#ifndef LEARNINGOPENGL_MATERIALS_H
#define LEARNINGOPENGL_MATERIALS_H

#include <glm/glm.hpp>

namespace opengl::materials
{
    struct
    {
        const glm::vec3 ambient{0.24725f, 0.195f, 0.0745f};
        const glm::vec3 diffuse{0.75164f, 0.60648f, 0.22648f};
        const glm::vec3 specular{0.628281f, 0.555802f, 0.366065f};
        const float shininess = 0.4f * 128;
    } gold;
}

#endif //LEARNINGOPENGL_MATERIALS_H
