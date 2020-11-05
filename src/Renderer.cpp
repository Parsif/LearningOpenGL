#include "Renderer.h"

#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

namespace opengl
{
    void Renderer::init(GLFWwindow *window)
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        // Setup Platform/Renderer bindings
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init();
        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
    }

    void Renderer::render(const Scene &scene)
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        renderMenu();
        renderScene(scene);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void Renderer::renderMenu()
    {
        imgui_addons::ImGuiFileBrowser file_dialog;
        bool open = false, save = false;
        if(ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("Menu"))
            {
                if (ImGui::MenuItem("Open", NULL))
                    open = true;
                if (ImGui::MenuItem("Save", NULL))
                    save = true;

                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }

        //Remember the name to ImGui::OpenPopup() and showFileDialog() must be same...
        if(open)
            ImGui::OpenPopup("Open File");
        if(save)
            ImGui::OpenPopup("Save File");

        /* Optional third parameter. Support opening only compressed rar/zip files.
         * Opening any other file will show error, return false and won't close the dialog.
         */
        if(file_dialog.showFileDialog("Open File", imgui_addons::ImGuiFileBrowser::DialogMode::OPEN, ImVec2(700, 310), ".rar,.zip,.7z"))
        {
            std::cout << file_dialog.selected_fn << std::endl;      // The name of the selected file or directory in case of Select Directory dialog mode
            std::cout << file_dialog.selected_path << std::endl;    // The absolute path to the selected file
        }
        if(file_dialog.showFileDialog("Save File", imgui_addons::ImGuiFileBrowser::DialogMode::SAVE, ImVec2(700, 310), ".png,.jpg,.bmp"))
        {
            std::cout << file_dialog.selected_fn << std::endl;      // The name of the selected file or directory in case of Select Directory dialog mode
            std::cout << file_dialog.selected_path << std::endl;    // The absolute path to the selected file
            std::cout << file_dialog.ext << std::endl;              // Access ext separately (For SAVE mode)
            //Do writing of files based on extension here
        }
    }


    void Renderer::renderScene(const Scene &scene)
    {
        for(auto&& model: scene.getModels())
        {
            //model.render();
        }
    }



}