#pragma once

namespace opengl
{
    class Layer
    {
    public:
        virtual void attach() = 0;
        virtual void detach() = 0;
        virtual void onEvent() = 0;
        virtual ~Layer() = default;
    };
}
