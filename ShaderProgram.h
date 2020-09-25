#ifndef LEARNINGOPENGL_SHADERPROGRAM_H
#define LEARNINGOPENGL_SHADERPROGRAM_H

#include "Shader.h"

#include <vector>
#include <string>

#include <GL/glew.h>

namespace opengl
{
    class ShaderProgram
    {
    private:
        int shader_program_id_;
    public:
        explicit ShaderProgram(const std::vector<Shader> &shaders);
        [[nodiscard]] inline auto GetId() const { return shader_program_id_; };
        void UseShaderProgram() const;
        void Uniform4f(const std::string &uniform_name, float value1, float value2, float value3, float value4) const;
    };
}


#endif //LEARNINGOPENGL_SHADERPROGRAM_H
