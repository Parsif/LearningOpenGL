#ifndef LEARNINGOPENGL_LAMP_H
#define LEARNINGOPENGL_LAMP_H

#include "ShaderProgram.h"
#include "buffers/VertexArray.h"
#include "buffers/VertexBuffer.h"

#include <glm/glm.hpp>

#include <optional>

namespace opengl
{
    class Lamp
    {
    private:
        VertexArray vertex_array_;
        glm::vec3 position_{1.2f, 1.0f, 2.0f};
        glm::mat4 model_{1.0f};
        std::optional<ShaderProgram> shader_program_;
    public:
        explicit Lamp(const VertexBuffer &vertex_buffer);
        void draw(const glm::mat4 &view_matrix, const glm::mat4 &projection_matrix) const;

        [[nodiscard]] inline auto getPosition() const { return position_; }
    };
}

#endif //LEARNINGOPENGL_LAMP_H
