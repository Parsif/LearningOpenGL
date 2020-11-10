#pragma once

#include <iostream>
#include "std_image.h"


namespace opengl
{
    enum class Direction
    {
        up, down, right, left
    };

    enum class TextureType
    {
        diffuse, specular
    };

    struct MousePos
    {
        float x{}, y{}, pitch = 0.f, yaw = -90.0f;
    };

}

