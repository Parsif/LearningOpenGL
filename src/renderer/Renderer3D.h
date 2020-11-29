#pragma once

#include "model/Model.h"
#include "ecs/Components.h"

namespace opengl
{
    class Renderer3D
    {
    public:
        static void renderModel(const Model& model, const glm::mat4& transform,  const glm::mat4& view_projection,
                                const glm::vec3& view_pos, const ShaderProgram& shader_program);

        static void renderPointLight(PointLightComponent point_light, const ShaderProgram &light_program,
                                     const ShaderProgram &basic_program);

    private:
    };
}


