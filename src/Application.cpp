#include "Application.h"

#include "EventHandler.h"
#include "buffers/VertexBuffer.h"
#include "drawable/Lamp.h"
#include "materials.h"


#include <glm/gtc/matrix_transform.hpp>

#include <iostream>


namespace opengl
{

    Application::Application()
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    }

    Application::~Application()
    {
        glfwTerminate();
    }

    void Application::Run()
    {

        const auto window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
        if (window == nullptr)
        {
            std::cout << "GLFW Window creation failed\n";
            glfwTerminate();
            return;
        }

        glfwMakeContextCurrent(window);
        if(glewInit() != GLEW_OK)
        {
            std::cout << "GLEW init failed\n";
            return;
        }

        glfwGetFramebufferSize(window, &window_width_, &window_height_);
        glViewport(0, 0, window_width_, window_height_);
        mouse_pos_.x = window_width_ / 2;
        mouse_pos_.y = window_height_ / 2;
        projection_ = glm::perspective(glm::radians(45.f), static_cast<float>(window_width_) / window_height_, 0.1f, 100.f);
        glEnable(GL_DEPTH_TEST);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        EventHandler::init(window, camera_, mouse_pos_);


        float vertices[] ={
                // positions          // normals           // texture coords
                -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
                0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
                0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
                0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
                -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
                -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

                -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
                0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
                0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
                0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
                -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
                -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

                -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
                -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
                -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
                -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
                -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
                -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

                0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
                0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
                0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
                0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
                0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
                0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

                -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
                0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
                0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
                0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
                -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

                -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
                0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
                0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
                0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
                -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
                -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
        };

        VertexBuffer vertex_buffer(vertices, sizeof(vertices));
        VertexArray object_vertex_array;
        object_vertex_array.bind();
            //coord attrib
            glVertexAttribPointer(0, 3, GL_FLOAT, false, 8 * sizeof(float), nullptr);
            glEnableVertexAttribArray(0);

            // normal vector attrib
            glVertexAttribPointer(1, 3, GL_FLOAT, false, 8 * sizeof(float),
                                  reinterpret_cast<const void *>(sizeof(float) * 3));
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(2, 2, GL_FLOAT, false, 8 * sizeof(float),
                                  reinterpret_cast<const void *>(sizeof(float) * 6));
            glEnableVertexAttribArray(2);
        object_vertex_array.unbind();

        const Shader light_vertex_shader("../src/shaders/lighting_vertex.glsl", GL_VERTEX_SHADER);
        const Shader light_fragment_shader("../src/shaders/lighting_fragment.glsl", GL_FRAGMENT_SHADER);
        const ShaderProgram light_shader_program({light_vertex_shader, light_fragment_shader});
        Lamp lamp(vertex_buffer);

        Texture container_texture("../res/container2.png");
        Texture container_specular_texture("../res/container2_specular.png");


        while (!glfwWindowShouldClose(window))
        {
            glfwPollEvents();
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            drawObject(light_shader_program, object_vertex_array, lamp.getPosition(), container_texture, container_specular_texture);
            lamp.draw(camera_->getViewMatrix(), projection_);
            glfwSwapBuffers(window);
        }
    }

    void Application::drawObject(const ShaderProgram &shader_program, const VertexArray &vertex_array, glm::vec3 light_pos, const Texture &texture, const Texture &specular_texture)
    {
        glm::mat4 model(1.0f);
        model = glm::rotate(model, glm::radians((GLfloat)glfwGetTime() * 50.0f), glm::vec3(0.5f, 1.f, 0.f));
        glm::vec3 light_color(1.0f, 1.0f, 1.0f);
        glm::vec3 object_color(1.0f, 0.4f, 0.31f);

        shader_program.UseShaderProgram();
        shader_program.uniformVec3f("u_view_pos", camera_->getGetPosition());
        shader_program.uniformVec3f("u_object_color", object_color);

        shader_program.uniformVec3f("u_light.ambient", glm::vec3(0.2f));
        shader_program.uniformVec3f("u_light.diffuse", glm::vec3(0.5f));
        shader_program.uniformVec3f("u_light.specular", glm::vec3(1.0f));
        shader_program.uniformVec3f("u_light.position", light_pos);

        shader_program.uniform1i("u_material.diffuse", 0);
        shader_program.uniform1i("u_material.specular", 1);
        shader_program.uniform1f("u_material.shininess", materials::gold.shininess);


        shader_program.uniformMatrix4fv("u_model", model);
        shader_program.uniformMatrix4fv("u_view", camera_->getViewMatrix());
        shader_program.uniformMatrix4fv("u_projection", projection_);

        texture.Bind();
        specular_texture.Bind(1);

        vertex_array.bind();
        glDrawArrays(GL_TRIANGLES, 0, 36);
        vertex_array.unbind();

        texture.UnBind();
        specular_texture.UnBind();

    }
}
