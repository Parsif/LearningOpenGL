#include "Renderer3D.h"

namespace opengl
{

    void Renderer3D::renderModel(const Model &model, const glm::mat4 &transform, const glm::mat4& view_projection)
    {
        const auto& lighting_program = s_shader_library.getLightningProgram();
        lighting_program.useShaderProgram();
        lighting_program.uniformMatrix4fv("u_model", transform);
        lighting_program.uniformMatrix4fv("u_view_projection", view_projection);
        model.render(lighting_program);
    }
}


