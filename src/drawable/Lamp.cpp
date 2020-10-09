#include "Lamp.h"

#include <glm/ext/matrix_transform.hpp>
#include <iostream>

namespace opengl
{
    Lamp::Lamp(const VertexBuffer &vertex_buffer)
    {
        vertex_array_.bind();
        //coord attrib
        vertex_buffer.bind();
        glVertexAttribPointer(0, 3, GL_FLOAT, false, 6 * sizeof(float), nullptr);
        glEnableVertexAttribArray(0);
        vertex_array_.unbind();

        model_ = glm::translate(model_, position_);
        model_ = glm::scale(model_, glm::vec3(0.2f));

        const Shader lamp_vertex_shader("../src/shaders/lamp_vertex.glsl", GL_VERTEX_SHADER);
        const Shader lamp_fragment_shader("../src/shaders/lamp_fragment.glsl", GL_FRAGMENT_SHADER);
        shader_program_ = ShaderProgram({lamp_fragment_shader, lamp_vertex_shader});
    }

    void Lamp::draw(const glm::mat4 &view_matrix, const glm::mat4 &projection_matrix) const
    {
        if (!shader_program_)
        {
            std::cerr << "Empty shader program\n";
            return;
        }
        shader_program_->UseShaderProgram();
        shader_program_->uniformMatrix4fv("u_model", model_);
        shader_program_->uniformMatrix4fv("u_view", view_matrix);
        shader_program_->uniformMatrix4fv("u_projection", projection_matrix);

        vertex_array_.bind();
            glDrawArrays(GL_TRIANGLES, 0, 36);
        vertex_array_.unbind();
    }
}

