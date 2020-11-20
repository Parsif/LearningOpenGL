#pragma once

#include "Layer.h"
#include "buffers/FrameBuffer.h"

namespace opengl
{
    class ImGuiLayer : public Layer
    {
    public:
        void onAttach() override;
        void onDetach() override;
        void onImGuiRender(const FrameBuffer& frame_buffer);
        void begin();
        void end();

    private:
        void renderDockingBegin();
        void renderDockingEnd();
        void setDarkThemeColors();
    };
}



