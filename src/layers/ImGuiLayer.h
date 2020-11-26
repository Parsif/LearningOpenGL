#pragma once

#include "Layer.h"
#include "buffers/FrameBuffer.h"
#include "panels/SceneHierarchyPanel.h"

namespace opengl
{
    class ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer() = default;
        ImGuiLayer(const std::shared_ptr<Scene>& scene);
        void onAttach() override;
        void onDetach() override;
        void onImGuiRender(const FrameBuffer& frame_buffer);
        void begin();
        void end();

    private:
        void renderDockingBegin();
        void renderDockingEnd();
        void setDarkThemeColors();
        SceneHierarchyPanel m_scene_hierarchy_panel;
    };
}



