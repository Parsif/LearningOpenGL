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
    public:
        ModelTexture(unsigned int id, std::string file_path, TextureType texture_type) : m_id(id), m_file_path(std::move(file_path)), m_texture_type(texture_type)
        {
            switch (m_texture_type)
            {
                case TextureType::Diffuse:
                    m_string_type = "diffuse";
                    break;
                case TextureType::Specular:
                    m_string_type = "specular";
                    break;
            }
        }

        void bind(unsigned int slot) const
        {
            glActiveTexture(GL_TEXTURE0 + slot);
            glBindTexture(GL_TEXTURE_2D, m_id);
        };
        [[nodiscard]] inline auto getFilePath() const { return m_file_path; }
        [[nodiscard]] inline auto getTextureType() const { return m_texture_type; }
        [[nodiscard]] inline auto getStringType() const { return m_string_type; }

    private:
        unsigned int m_id;
        std::string m_file_path;
        std::string m_string_type;
        TextureType m_texture_type;
    };

    class Mesh
    {
    public:
        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<ModelTexture> textures);
        void render(const ShaderProgram &shader_program) const;

    private:
        VertexArray m_vertex_array;
        std::shared_ptr<VertexBuffer> m_vertex_buffer;
        std::shared_ptr<IndexBuffer> m_index_buffer;

        std::vector<Vertex> m_vertices;
        std::vector<unsigned int> m_indices;
        std::vector<ModelTexture> m_textures;
    };
}

