#pragma once

#include "pch.h"

#include "model/Model.h"
#include "Camera.h"

namespace opengl
{
    class Entity
    {
    public:
        Entity(const std::string& model_filepath, const ShaderProgram& shader_program);

        void render(const Camera& camera);

    private:
        ShaderProgram m_shader_program;
        std::optional<Model> m_model;
        glm::mat4 m_model_matrix{1.0f};
        glm::vec3 m_translate, m_scale, m_rotate;
    };
}


