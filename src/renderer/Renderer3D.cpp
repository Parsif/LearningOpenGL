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



    void Renderer3D::renderPointLight(PointLightComponent point_light, const ShaderProgram &light_program,
                                      const ShaderProgram &basic_program)
    {
        light_program.uniformVec3f("u_point_light.albedo", point_light.albedo);
        light_program.uniformVec3f("u_point_light.position", point_light.position);
        light_program.uniform1f("u_point_light.constant", point_light.constant);
        light_program.uniform1f("u_point_light.linear", point_light.linear);
        light_program.uniform1f("u_point_light.quadratic", point_light.quadratic);


        float offset = 15;
        float lines[] = {
                point_light.position.x - offset, point_light.position.y, point_light.position.z,
                point_light.position.x + offset, point_light.position.y, point_light.position.z,
                point_light.position.x, point_light.position.y - offset, point_light.position.z,
                point_light.position.x, point_light.position.y + offset, point_light.position.z,
                point_light.position.x, point_light.position.y, point_light.position.z - offset,
                point_light.position.x, point_light.position.y, point_light.position.z + offset,
        };
        VertexBuffer vertex_buffer(lines, sizeof(lines));
        BufferLayout layout = {
                {ShaderDataType::Float3}
        };
        basic_program.useShaderProgram();
        glDrawArrays(GL_LINES, 0, 2);
    }
}


