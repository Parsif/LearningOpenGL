#include "Application.h"


#include "ShaderProgram.h"
#include "buffers/VertexArray.h"
#include "buffers/VertexBuffer.h"
#include "buffers/IndexBuffer.h"
#include "EventHandler.h"

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
        glEnable(GL_DEPTH_TEST);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        EventHandler::init(window, camera_, mouse_pos_);


        float vertices[] ={
                // coord              // texture_coord
                -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
                0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
                0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

                -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
                0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
                0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
                -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
                -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

                -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

                0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

                -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
                0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
                0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
                -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

                -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
                0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
                -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
        };
        unsigned int indices[] = {0, 1, 2, 2, 1, 3};

        VertexBuffer vertex_buffer(vertices, sizeof(vertices));
        VertexArray object_vertex_array, lamp_vertex_array;
        object_vertex_array.bind();
            IndexBuffer object_index_buffer(indices, sizeof(indices));
            //coord attrib
            glVertexAttribPointer(0, 3, GL_FLOAT, false, 5 * sizeof(float), nullptr);
            glEnableVertexAttribArray(0);

            //texture coord attrib
            glVertexAttribPointer(1, 2, GL_FLOAT, false, 5 * sizeof(float),
                                  reinterpret_cast<const void *>(sizeof(float) * 3));
            glEnableVertexAttribArray(1);
        object_vertex_array.unbind();

        lamp_vertex_array.bind();
            IndexBuffer light_index_buffer(indices, sizeof(indices));
            //coord attrib
            glVertexAttribPointer(0, 3, GL_FLOAT, false, 5 * sizeof(float), nullptr);
            glEnableVertexAttribArray(0);
        lamp_vertex_array.unbind();


        const Shader light_vertex_shader("../src/shaders/lighting_vertex.glsl", GL_VERTEX_SHADER);
        const Shader light_fragment_shader("../src/shaders/lighting_fragment.glsl", GL_FRAGMENT_SHADER);
        const ShaderProgram light_shader_program({light_vertex_shader, light_fragment_shader});

        const Shader lamp_vertex_shader("../src/shaders/lamp_vertex.glsl", GL_VERTEX_SHADER);
        const Shader lamp_fragment_shader("../src/shaders/lamp_fragment.glsl", GL_FRAGMENT_SHADER);
        const ShaderProgram lamp_shader_program({lamp_fragment_shader, lamp_vertex_shader});

        while (!glfwWindowShouldClose(window))
        {
            glfwPollEvents();
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glm::mat4 projection(1.0f);
            projection = glm::perspective(glm::radians(45.f), static_cast<float>(window_width_) / window_height_, 0.1f, 100.f);
            drawObject(light_shader_program, object_vertex_array, projection);
            drawLamp(lamp_shader_program, lamp_vertex_array, projection);

            glfwSwapBuffers(window);
        }
    }

    void Application::drawLamp(const ShaderProgram &shader_program, const VertexArray &vertex_array, const glm::mat4 &projection)
    {
        glm::mat4 model(1.0f);
        model = glm::translate(model, glm::vec3(1.2f, 0.0f, 2.0f));
        model = glm::scale(model, glm::vec3(0.2f));

        shader_program.UseShaderProgram();
        shader_program.UniformMatrix4fv("u_model", model);
        shader_program.UniformMatrix4fv("u_view", camera_->getViewMatrix());
        shader_program.UniformMatrix4fv("u_projection", projection);

        vertex_array.bind();
        glDrawArrays(GL_TRIANGLES, 0, 36);
        vertex_array.unbind();
    }

    void Application::drawObject(const ShaderProgram &shader_program, const VertexArray &vertex_array, const glm::mat4 &projection)
    {
        glm::mat4 model(1.0f);
        model = glm::rotate(model, glm::radians((GLfloat)glfwGetTime() * 50.0f), glm::vec3(0.5f, 1.f, 0.f));
        glm::vec3 light_color(1.0f, 1.0f, 1.0f);
        glm::vec3 object_color(1.0f, 0.5f, 0.31f);

        shader_program.UseShaderProgram();
        shader_program.uniformVec3f("u_object_color", object_color);
        shader_program.uniformVec3f("u_light_color", light_color);
        shader_program.UniformMatrix4fv("u_model", model);
        shader_program.UniformMatrix4fv("u_view", camera_->getViewMatrix());
        shader_program.UniformMatrix4fv("u_projection", projection);

        vertex_array.bind();
        glDrawArrays(GL_TRIANGLES, 0, 36);
        vertex_array.unbind();
    }
}
