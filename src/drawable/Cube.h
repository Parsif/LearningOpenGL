#ifndef LEARNINGOPENGL_CUBE_H
#define LEARNINGOPENGL_CUBE_H

#include "ShaderProgram.h"
#include "Camera.h"
#include "FileTexture.h"
#include "buffers/VertexArray.h"
#include "buffers/VertexBuffer.h"

#include <glm/glm.hpp>

#include <optional>
#include <memory>


namespace opengl
{
    class Cube
    {
    private:
        VertexArray vertex_array_;
        glm::vec3 position_{0.0f, 0.0f, 0.0f};
        glm::vec3 color_{1.0f, 0.4f, 0.31f};
        glm::mat4 model_matrix_{1.0f};

        std::optional<ShaderProgram> light_shader_program_;
        FileTexture container_texture_{"../res/container2.png"};
        FileTexture container_specular_texture{"../res/container2_specular.png"};
    public:
        explicit Cube(const VertexBuffer &vertex_buffer);
        void render(const std::shared_ptr<Camera> &camera, const glm::mat4 &projection_matrix, const glm::vec3 &light_pos);
    };
}



#endif //LEARNINGOPENGL_CUBE_H
