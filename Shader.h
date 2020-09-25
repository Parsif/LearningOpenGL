#ifndef LEARNINGOPENGL_SHADER_H
#define LEARNINGOPENGL_SHADER_H

#include <string>


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



#endif //LEARNINGOPENGL_SHADER_H
