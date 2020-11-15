#include "SceneObject.h"

namespace opengl
{
    SceneObject::SceneObject(const std::string& model_filepath, const ShaderProgram& shader_program, const glm::vec3& position,
                             const glm::vec3& scale)
    : m_shader_program(shader_program), m_position(position)
    {
        m_model = Model(model_filepath);
        m_model_matrix = glm::translate(m_model_matrix, position);
        m_model_matrix = glm::scale(m_model_matrix, scale);
    }

    void SceneObject::render(const Camera& camera)
    {
        m_shader_program.useShaderProgram();
        m_shader_program.uniformMatrix4fv("model",  m_model_matrix);
        m_shader_program.uniformMatrix4fv("view",  camera.getViewMatrix());
        m_shader_program.uniformMatrix4fv("projection", camera.getProjectionMatrix());
        m_model->render(m_shader_program);
    }
}

