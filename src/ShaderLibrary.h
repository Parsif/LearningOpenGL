#pragma once

#include "ShaderProgram.h"

namespace opengl
{
    class ShaderLibrary
    {
    public:
        ShaderLibrary();

        [[nodiscard]] inline const auto& getLightningProgram() const { return lightning_program; }
    private:
        ShaderProgram lightning_program;
    };
}




