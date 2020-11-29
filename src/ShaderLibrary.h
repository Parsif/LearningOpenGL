#pragma once

#include "ShaderProgram.h"

namespace opengl
{
    class ShaderLibrary
    {
    public:
        ShaderLibrary();

        [[nodiscard]] inline const auto& getBasicProgram() const { return m_basic_program; }
        [[nodiscard]] inline const auto& getLightningProgram() const { return m_lightning_program; }
    private:
        ShaderProgram m_basic_program;
        ShaderProgram m_lightning_program;
    };
}




