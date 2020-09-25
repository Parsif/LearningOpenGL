#include "ShaderProgram.h"

#include <iostream>


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

    void ShaderProgram::Uniform4f(const std::string &uniform_name, float value1, float value2, float value3, float value4) const
    {
        const auto vertexColorLocation = glGetUniformLocation(shader_program_id_, uniform_name.c_str());
        glUniform4f(vertexColorLocation, value1, value2, value3, value4);

    }

}
