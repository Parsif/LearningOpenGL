#pragma once

#include "buffers/FrameBuffer.h"
#include "panels/SceneHierarchyPanel.h"

namespace opengl
{
    class ImGuiLayer
    {
    public:
        static void onAttach(const std::shared_ptr<Scene>& scene);
        static void onDetach();
        static void onImGuiRender(const FrameBuffer& frame_buffer);
        static void begin();
        static void end();

        [[nodiscard]] static inline bool isSceneViewHovered() { return s_scene_view_hovered; }

    private:
        static void renderDockingBegin();
        static void renderDockingEnd();
        static void setDarkThemeColors();
        static inline SceneHierarchyPanel s_scene_hierarchy_panel;
        static inline bool s_scene_view_hovered = false;
    };
}



