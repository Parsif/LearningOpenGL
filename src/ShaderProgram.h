#ifndef LEARNINGOPENGL_SHADERPROGRAM_H
#define LEARNINGOPENGL_SHADERPROGRAM_H

#include <GL/glew.h>
#include "Shader.h"

#include <vector>
#include <string>

#include <glm/glm.hpp>


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
        void uniform1i(const std::string &uniform_name, int value1) const;
        void uniform1f(const std::string &uniform_name, float value1) const;
        void uniform4f(const std::string &uniform_name, float value1, float value2, float value3, float value4) const;
        void uniformMatrix4fv(const std::string &uniform_name, const glm::mat4 &matrix) const;
        void uniformVec3f(const std::string &uniform_name, const glm::vec3 &vec) const;
    };
}


#endif //LEARNINGOPENGL_SHADERPROGRAM_H
