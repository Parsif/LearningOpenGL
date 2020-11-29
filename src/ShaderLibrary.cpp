#include "ShaderLibrary.h"

namespace opengl
{
    ShaderLibrary::ShaderLibrary()
    {
        m_basic_program = ShaderProgram({Shader("../src/shaders/basic_vertex.glsl",   GL_VERTEX_SHADER),
                                             Shader("../src/shaders/basic_fragment.glsl", GL_FRAGMENT_SHADER)});

        m_lightning_program = ShaderProgram({Shader("../src/shaders/lighting_vertex.glsl",   GL_VERTEX_SHADER),
                                           Shader("../src/shaders/lighting_fragment.glsl", GL_FRAGMENT_SHADER)});
    }
}

