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

    void Application::Run()
    {
        const auto window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
        if (window == nullptr)
        {
            std::cout << "GLFW Window creation failed\n";
            glfwTerminate();
            return;
        }
        EventHandler::init(window, camera_);

        glfwMakeContextCurrent(window);
        if(glewInit() != GLEW_OK)
        {
            std::cout << "GLEW init failed\n";
            return;
        }

        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);
        glEnable(GL_DEPTH_TEST);

    	
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
        VertexArray vertex_array;
        vertex_array.bind();
            IndexBuffer index_buffer(indices, sizeof(indices));
    	
            //coord attrib
            glVertexAttribPointer(0, 3, GL_FLOAT, false, 5 * sizeof(float), nullptr);
            glEnableVertexAttribArray(0);

            //texture coord attrib
            glVertexAttribPointer(1, 2, GL_FLOAT, false, 5 * sizeof(float),
                                  reinterpret_cast<const void *>(sizeof(float) * 3));
            glEnableVertexAttribArray(1);
        vertex_array.unbind();

        const Shader vertex_shader("../src/shaders/vertex.glsl", GL_VERTEX_SHADER);
        const Shader fragment_shader("../src/shaders/fragment.glsl", GL_FRAGMENT_SHADER);
        const ShaderProgram shader_program({vertex_shader, fragment_shader});

        while (!glfwWindowShouldClose(window))
        {
            glm::mat4 projection(1.0f);
            projection = glm::perspective(glm::radians(45.f), static_cast<float>(width) / height, 0.1f, 100.f);
            glm::mat4 model(1.0f);
            model = glm::rotate(model, glm::radians((GLfloat)glfwGetTime() * 50.0f), glm::vec3(0.5f, 1.f, 0.f));

            glfwPollEvents();
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            shader_program.UseShaderProgram();
            glm::vec3 light_color(1.0f, 1.0f, 1.0f);
            glm::vec3 toy_color(1.0f, 0.5f, 0.31f);
            shader_program.uniformVec3f("u_object_color", toy_color);
            shader_program.uniformVec3f("u_light_color", light_color);
            shader_program.UniformMatrix4fv("u_model", model);
            shader_program.UniformMatrix4fv("u_view", camera_->getViewMatrix());
            shader_program.UniformMatrix4fv("u_projection", projection);

            vertex_array.bind();
                glDrawArrays(GL_TRIANGLES, 0, 36);
            vertex_array.unbind();
            glfwSwapBuffers(window);
        }
    }

    Application::~Application()
    {
        glfwTerminate();
    }
}
