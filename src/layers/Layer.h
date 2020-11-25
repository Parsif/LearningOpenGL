#pragma once

#include "renderer/Renderer3D.h"

namespace opengl
{
    class Layer
    {
    public:
        virtual void onAttach() = 0;
        virtual void onDetach() = 0;
        virtual ~Layer() = default;
    };

}
