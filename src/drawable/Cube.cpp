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

        light_shader_program_->UseShaderProgram();
        light_shader_program_->uniformVec3f("u_view_pos", camera->getGetPosition());
        light_shader_program_->uniformVec3f("u_object_color", color_);

        light_shader_program_->uniformVec3f("u_dir_light.ambient", glm::vec3(0.2f));
        light_shader_program_->uniformVec3f("u_dir_light.diffuse", glm::vec3(0.5f));
        light_shader_program_->uniformVec3f("u_dir_light.specular", glm::vec3(1.0f));
        light_shader_program_->uniformVec3f("u_dir_light.direction", glm::vec3(-0.2f, -1.0f, -0.3f));

        light_shader_program_->uniformVec3f("u_point_light.ambient", glm::vec3(0.2f));
        light_shader_program_->uniformVec3f("u_point_light.diffuse", glm::vec3(0.5f));
        light_shader_program_->uniformVec3f("u_point_light.specular", glm::vec3(1.0f));
        light_shader_program_->uniformVec3f("u_point_light.position", light_pos);
        light_shader_program_->uniform1f("u_point_light.constant", 1.0f);
        light_shader_program_->uniform1f("u_point_light.linear", 0.09f);
        light_shader_program_->uniform1f("u_point_light.quadratic", 0.032f);

        light_shader_program_->uniformVec3f("u_spot_light.ambient", glm::vec3(0.2f));
        light_shader_program_->uniformVec3f("u_spot_light.diffuse", glm::vec3(0.5f));
        light_shader_program_->uniformVec3f("u_spot_light.specular", glm::vec3(1.0f));
        light_shader_program_->uniformVec3f("u_spot_light.direction", camera->getGetFront());
        light_shader_program_->uniformVec3f("u_spot_light.position", camera->getGetPosition());
        light_shader_program_->uniform1f("u_spot_light.cut_off", glm::cos(glm::radians(12.5f)));
        light_shader_program_->uniform1f("u_spot_light.outer_cut_off", glm::cos(glm::radians(17.0f)));


        light_shader_program_->uniform1i("u_material.diffuse", 0);
        light_shader_program_->uniform1i("u_material.specular", 1);
        light_shader_program_->uniform1f("u_material.shininess", 0.4f);

        light_shader_program_->uniformMatrix4fv("u_view", camera->getViewMatrix());
        light_shader_program_->uniformMatrix4fv("u_projection", projection_matrix);

        container_texture_.Bind();
        container_specular_texture.Bind(1);

        vertex_array_.bind();
        glm::vec3 cubePositions[] = {
                glm::vec3( 0.0f,  0.0f,  0.0f),
                glm::vec3( 2.0f,  5.0f, -15.0f),
                glm::vec3(-1.5f, -2.2f, -2.5f),
                glm::vec3(-3.8f, -2.0f, -12.3f),
                glm::vec3( 2.4f, -0.4f, -3.5f),
                glm::vec3(-1.7f,  3.0f, -7.5f),
                glm::vec3( 1.3f, -2.0f, -2.5f),
                glm::vec3( 1.5f,  2.0f, -2.5f),
                glm::vec3( 1.5f,  0.2f, -1.5f),
                glm::vec3(-1.3f,  1.0f, -1.5f)
        };

        for (auto&& cube_position : cubePositions)
        {
            model_matrix_ = glm::mat4(1.0f);
            model_matrix_ = glm::translate(model_matrix_, cube_position);
            model_matrix_ = glm::rotate(model_matrix_, glm::radians((GLfloat)glfwGetTime() * 50.0f), glm::vec3(0.5f, 1.f, 0.f));
            light_shader_program_->uniformMatrix4fv("u_model", model_matrix_);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        vertex_array_.unbind();

        container_texture_.UnBind();
        container_specular_texture.UnBind();

    }
}

