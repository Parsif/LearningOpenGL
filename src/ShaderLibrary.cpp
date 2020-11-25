#include "ShaderLibrary.h"

namespace opengl
{
    ShaderLibrary::ShaderLibrary()
    {
        lightning_program = ShaderProgram({Shader("../src/shaders/lighting_vertex.glsl",   GL_VERTEX_SHADER),
                                           Shader("../src/shaders/lighting_fragment.glsl", GL_FRAGMENT_SHADER)});
    }
}

