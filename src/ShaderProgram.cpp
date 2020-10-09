#include "ShaderProgram.h"

#include <iostream>

#include <glm/gtc/type_ptr.hpp>

namespace opengl
{
    ShaderProgram::ShaderProgram(const std::vector<Shader> &shaders)
    {
        shader_program_id_ = glCreateProgram();
        for(const auto& shader : shaders)
        {
            glAttachShader(shader_program_id_, shader.get_shader_id());
        }
        glLinkProgram(shader_program_id_);

        int success;
        glGetProgramiv(shader_program_id_, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            char info_log[512];
            glGetProgramInfoLog(shader_program_id_, sizeof(info_log), nullptr, info_log);
            std::cerr << info_log << '\n';
        }

        for(const auto& shader : shaders)
        {
            glDeleteShader(shader.get_shader_id());
        }
    }

    void ShaderProgram::UseShaderProgram() const
    {
        glUseProgram(shader_program_id_);
    }

    void ShaderProgram::uniform1i(const std::string &uniform_name, int value1) const
    {
        const auto uniform_location = glGetUniformLocation(shader_program_id_, uniform_name.c_str());
        glUniform1i(uniform_location, value1);
    }

    void ShaderProgram::uniform1f(const std::string &uniform_name, float value1) const
    {
        const auto uniform_location = glGetUniformLocation(shader_program_id_, uniform_name.c_str());
        glUniform1f(uniform_location, value1);
    }

    void ShaderProgram::uniform4f(const std::string &uniform_name, float value1, float value2, float value3, float value4) const
    {
        const auto uniform_location = glGetUniformLocation(shader_program_id_, uniform_name.c_str());
        glUniform4f(uniform_location, value1, value2, value3, value4);
    }

    void ShaderProgram::uniformMatrix4fv(const std::string &uniform_name, const glm::mat4 &matrix) const
    {
        const auto uniform_location = glGetUniformLocation(shader_program_id_, uniform_name.c_str());
        glUniformMatrix4fv(uniform_location, 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void ShaderProgram::uniformVec3f(const std::string &uniform_name, const glm::vec3 &vec) const
    {
        const auto uniform_location = glGetUniformLocation(shader_program_id_, uniform_name.c_str());
        glUniform3f(uniform_location, vec.x, vec.y, vec.z);
    }


}
