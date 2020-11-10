#include "Entity.h"

namespace opengl
{
    Entity::Entity(const std::string& model_filepath, const ShaderProgram& shader_program) : m_shader_program(shader_program)
    {
        m_model = Model(model_filepath);
    }

    void Entity::render(const Camera& camera)
    {
        m_shader_program.UseShaderProgram();
        m_shader_program.uniformMatrix4fv("model",  m_model_matrix);
        m_shader_program.uniformMatrix4fv("view",  camera.getViewMatrix());
        m_shader_program.uniformMatrix4fv("projection", camera.getProjectionMatrix());
        m_model->render(m_shader_program);
    }
}


