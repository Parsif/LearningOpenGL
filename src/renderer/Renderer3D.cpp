#include "Renderer3D.h"

namespace opengl
{

    void Renderer3D::renderModel(const Model &model, const glm::mat4 &transform, const glm::mat4& view_projection,
                                 const glm::vec3& view_pos, const ShaderProgram& shader_program)
    {
        shader_program.uniformMatrix4fv("u_model", transform);
        shader_program.uniformMatrix4fv("u_view_projection", view_projection);
        shader_program.uniformVec3f("u_view_pos", view_pos);
        model.render(shader_program);
    }

    void Renderer3D::renderPointLight(PointLightComponent point_light, const ShaderProgram &shader_program)
    {
        shader_program.uniformVec3f("u_point_light.ambient", point_light.ambient);
        shader_program.uniformVec3f("u_point_light.diffuse", point_light.diffuse);
        shader_program.uniformVec3f("u_point_light.specular", point_light.specular);
        shader_program.uniformVec3f("u_point_light.position", point_light.position);
        shader_program.uniform1f("u_point_light.constant", point_light.constant);
        shader_program.uniform1f("u_point_light.linear", point_light.linear);
        shader_program.uniform1f("u_point_light.quadratic", point_light.quadratic);

    }
}


