#pragma once

#include "pch.h"

#include "model/Model.h"
#include "Camera.h"

namespace opengl
{
    class Entity
    {
    public:
        Entity(const std::string& model_filepath, const ShaderProgram& shader_program, const glm::vec3& position = glm::vec3(0.0f));

        [[nodiscard]] auto inline getPosition() const { return m_position; }
        void render(const Camera& camera);

    private:
        ShaderProgram m_shader_program;
        std::optional<Model> m_model;
        glm::mat4 m_model_matrix{1.0f};
        glm::vec3 m_position;
        glm::vec3 m_translate, m_scale, m_rotate;
        std::string m_name;
    };
}


