#pragma once

#include "Layer.h"

namespace opengl
{
    class ImGuiLayer : public Layer
    {
    public:
        void onAttach() override;
        void onDetach() override;
        void onImGuiRender();
        void begin();
        void end();

    private:
        void setDarkThemeColors();
    };
}



