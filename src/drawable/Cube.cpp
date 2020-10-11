#include "Cube.h"

#include <glm/ext/matrix_transform.hpp>
#include <GLFW/glfw3.h>

#include <iostream>

namespace opengl
{
    Cube::Cube(const VertexBuffer &vertex_buffer)
    {
        vertex_array_.bind();
        //coord attrib
        vertex_buffer.bind();
        glVertexAttribPointer(0, 3, GL_FLOAT, false, 8 * sizeof(float), nullptr);
        glEnableVertexAttribArray(0);

        // normal vector attrib
        glVertexAttribPointer(1, 3, GL_FLOAT, false, 8 * sizeof(float),
                              reinterpret_cast<const void *>(sizeof(float) * 3));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, false, 8 * sizeof(float),
                              reinterpret_cast<const void *>(sizeof(float) * 6));
        glEnableVertexAttribArray(2);
        vertex_array_.unbind();


        const Shader light_vertex_shader("../src/shaders/lighting_vertex.glsl", GL_VERTEX_SHADER);
        const Shader light_fragment_shader("../src/shaders/lighting_fragment.glsl", GL_FRAGMENT_SHADER);
        light_shader_program_ = ShaderProgram({light_vertex_shader, light_fragment_shader});
    }

    void Cube::render(const std::shared_ptr<Camera> &camera, const glm::mat4 &projection_matrix, const glm::vec3 &light_pos)
    {
        if (!light_shader_program_)
        {
            std::cerr << "Empty shader program\n";
            return;
        }
        model_ = glm::mat4{1.f};
        model_ = glm::rotate(model_, glm::radians((GLfloat)glfwGetTime() * 50.0f), glm::vec3(0.5f, 1.f, 0.f));

        light_shader_program_->UseShaderProgram();
        light_shader_program_->uniformVec3f("u_view_pos", camera->getGetPosition());
        light_shader_program_->uniformVec3f("u_object_color", color_);

        light_shader_program_->uniformVec3f("u_light.ambient", glm::vec3(0.2f));
        light_shader_program_->uniformVec3f("u_light.diffuse", glm::vec3(0.5f));
        light_shader_program_->uniformVec3f("u_light.specular", glm::vec3(1.0f));
        light_shader_program_->uniformVec3f("u_light.position", light_pos);

        light_shader_program_->uniform1i("u_material.diffuse", 0);
        light_shader_program_->uniform1i("u_material.specular", 1);
        light_shader_program_->uniform1f("u_material.shininess", 0.4f);

        light_shader_program_->uniformMatrix4fv("u_model", model_);
        light_shader_program_->uniformMatrix4fv("u_view", camera->getViewMatrix());
        light_shader_program_->uniformMatrix4fv("u_projection", projection_matrix);

        container_texture_.Bind();
        container_specular_texture.Bind(1);

        vertex_array_.bind();
        glDrawArrays(GL_TRIANGLES, 0, 36);
        vertex_array_.unbind();

        container_texture_.UnBind();
        container_specular_texture.UnBind();

    }
}

