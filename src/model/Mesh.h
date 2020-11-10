#pragma once

#include "pch.h"

#include "global.h"
#include "buffers/VertexArray.h"
#include "buffers/Buffer.h"
#include "ShaderProgram.h"
#include "FileTexture.h"


namespace opengl
{
    struct Vertex
    {
        glm::vec3 position, normal;
        glm::vec2 tex_coords;
    };

    class ModelTexture
    {
    private:
        unsigned int id_;
        std::string file_path_;
        std::string string_type_;
        TextureType texture_type_;

    public:
        ModelTexture(unsigned int id, std::string file_path, TextureType texture_type) : id_(id), file_path_(std::move(file_path)), texture_type_(texture_type)
        {
            switch (texture_type_)
            {
                case TextureType::diffuse:
                    string_type_ = "diffuse";
                    break;
                case TextureType::specular:
                    string_type_ = "specular";
                    break;
            }
        }

        void bind(unsigned int slot)
        {
            glActiveTexture(GL_TEXTURE0 + slot);
            glBindTexture(GL_TEXTURE_2D, id_);
        };
        [[nodiscard]] inline auto getFilePath() const { return file_path_; }
        [[nodiscard]] inline auto getTextureType() const { return texture_type_; }
        [[nodiscard]] inline auto getStringType() const { return string_type_; }
    };

    class Mesh
    {
    private:
        VertexArray vertex_array_;
        std::unique_ptr<VertexBuffer> vertex_buffer_;
        std::unique_ptr<IndexBuffer> index_buffer_;

        std::vector<Vertex> vertices_;
        std::vector<unsigned int> indices_;
        std::vector<ModelTexture> textures_;

    public:
        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<ModelTexture> textures);
        void render(const ShaderProgram &shader_program);
    };
}

