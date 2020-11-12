#pragma once

#include "renderer/EngineRenderer.h"

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
