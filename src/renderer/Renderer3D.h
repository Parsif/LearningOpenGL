#pragma once

#include "ShaderLibrary.h"
#include "model/Model.h"

namespace opengl
{
    class Renderer3D
    {
    public:
        static void renderModel(const Model& model, const glm::mat4& transform, const glm::mat4& view_projection);
//        static void renderPointLight(PointLightComponent point_light_component);

    private:
       inline static ShaderLibrary s_shader_library;
    };
}


