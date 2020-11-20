#pragma once

#include "pch.h"
#include "Shader.h"
#include "types.h"

#include <glm/glm.hpp>

namespace opengl
{
    class ShaderProgram
    {

    public:
        explicit ShaderProgram(const std::vector<Shader> &shaders);
        [[nodiscard]] inline auto getId() const { return m_shader_program_id; };
        void useShaderProgram() const;
        void uniform1i(const std::string &uniform_name, int value1) const;
        void uniform1f(const std::string &uniform_name, float value1) const;
        void uniform4f(const std::string &uniform_name, float value1, float value2, float value3, float value4) const;
        void uniformMatrix4fv(const std::string &uniform_name, const glm::mat4 &matrix) const;
        void uniformVec3f(const std::string &uniform_name, const glm::vec3 &vec) const;
    private:
        rendererIdType m_shader_program_id;
    };
}

