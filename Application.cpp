#include "Application.h"
#include "ShaderProgram.h"
#include "Texture.h"

#include <GLFW/glfw3.h>

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

        glfwMakeContextCurrent(window);
        if(glewInit() != GLEW_OK)
        {
            std::cout << "GLEW init failed\n";
            return;
        }

        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);

        float vertices[] ={
                // coord             // color        //texture_coord
               -0.5f,  -0.5f,  0.0f,  1.f, 0.f, 0.f,  0.0f, 0.0f,
               -0.5f,   0.5f,  0.0f,  0.f, 1.f, 0.f,  0.0f, 1.0f,
                0.5f,  -0.5f,  0.0f,  0.f, 0.f, 1.f,  1.0f, 0.0f,
                0.5f,   0.5f,  0.0f,  0.f, 0.f, 0.f,  1.0f, 1.0f
        };

        unsigned int indices[] = {0, 1, 2, 2, 1, 3};

        unsigned int vbo, vao, ibo;
        glGenBuffers(1, &vbo);
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &ibo);

        glBindVertexArray(vao);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            //coord attrib
            glVertexAttribPointer(0, 3, GL_FLOAT, false, 8 * sizeof(float), nullptr);
            glEnableVertexAttribArray(0);

            //color attrib
            glVertexAttribPointer(1, 3, GL_FLOAT, false, 8 * sizeof(float),
                                  reinterpret_cast<const void *>(sizeof(float) * 3));
            glEnableVertexAttribArray(1);

            //texture coord attrib
            glVertexAttribPointer(2, 2, GL_FLOAT, false, 8 * sizeof(float),
                                  reinterpret_cast<const void *>(sizeof(float) * 6));
            glEnableVertexAttribArray(2);

        glBindVertexArray(0);

        Shader vertex_shader("../vertex.glsl", GL_VERTEX_SHADER);
        Shader fragment_shader("../fragment.glsl", GL_FRAGMENT_SHADER);
        ShaderProgram shader_program({vertex_shader, fragment_shader});

        Texture face_texture("../res/awesomeface.png");
        Texture container_texture("../res/container.jpg");

        glm::mat4 trans;
        trans = glm::rotate(trans,glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
        trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));


        glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
        glm::mat4 trans2;
        trans2 = glm::translate(trans2, glm::vec3(1.0f, 1.0f, 0.0f));
        vec = trans2 * vec;
        std::cout << vec.x << vec.y << vec.z << std::endl;

        while (!glfwWindowShouldClose(window))
        {
            glfwPollEvents();
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            shader_program.UseShaderProgram();
            shader_program.Uniform1i("u_face_texture", 0);
            shader_program.Uniform1i("u_container_texture", 1);
            shader_program.UniformMatrix4fv("u_matrix", trans);
            glBindVertexArray(vao);
                face_texture.Bind();
                container_texture.Bind(1);
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
                container_texture.UnBind();
                face_texture.UnBind();
            glBindVertexArray(0);

            glfwSwapBuffers(window);
        }
        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vbo);
        glDeleteBuffers(1, &ibo);
    }

    Application::~Application()
    {
        glfwTerminate();
    }
}