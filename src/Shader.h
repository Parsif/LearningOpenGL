#pragma once

#include "pch.h"


namespace opengl
{
    class Shader
    {
    private:
        unsigned int shader_id_;
        int shader_type_;
    public:
        Shader(const std::string &shader_filename, int shader_type);
        [[nodiscard]] inline auto get_shader_id() const { return shader_id_; }
    };
}

