#include "Shader.h"

#include <fstream>
#include <iostream>

#include <GL/glew.h>

namespace OpenGL
{
    Shader::Shader(const std::string &shader_filename, const int shader_type) : shader_type_(shader_type)
    {
        std::ifstream shader_stream(shader_filename);
        if (!shader_stream.is_open())
        {
            std::cerr << "Can't open file: " << shader_filename << '\n';
            return;
        }
        const std::string shader_content((std::istreambuf_iterator<char>(shader_stream)), std::istreambuf_iterator<char>());
        shader_stream.close();

        shader_id_ = glCreateShader(shader_type_);
        const auto shader_source = shader_content.c_str();
        glShaderSource(shader_id_, 1, &shader_source, nullptr);
        glCompileShader(shader_id_);

        int success;
        glGetShaderiv(shader_id_, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            char info_log[512];
            glGetShaderInfoLog(shader_id_, sizeof(info_log), nullptr, info_log);
            std::cerr << info_log << '\n';
        }

    }
}
