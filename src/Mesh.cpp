#include "Mesh.h"

#include <utility>

namespace opengl
{
    Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures) :
            vertices_(std::move(vertices)), indices_(std::move(indices)), textures_(std::move(textures))
    {
        vertex_array_.bind();
        vertex_buffer_ = VertexBuffer(vertices.data(), vertices.size() * sizeof(decltype (vertices)::value_type));
        index_buffer_ = IndexBuffer(indices.data(), indices.size() * sizeof(decltype (vertices)::value_type));

        // vertex position
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
        // vertex normals
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<const void *>(Vertex::getNormalOffset()));
        // vertex texture coords
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),  reinterpret_cast<const void *>(Vertex::getTexCoordOffset()));
        vertex_array_.unbind();

    }

    void Mesh::render(const ShaderProgram &shader_program)
    {
        unsigned int diffuse_counter = 1;
        unsigned int specular_counter = 1;

        for (unsigned int i = 0; i < textures_.size(); ++i)
        {
            textures_[i].bind(i);
            std::string texture_number;
            if(textures_[i].getTextureType() == TextureType::diffuse)
                texture_number = std::to_string(diffuse_counter++);
            else if(textures_[i].getTextureType() == TextureType::diffuse)
                texture_number = std::to_string(specular_counter++);
            shader_program.uniform1i("material." + textures_[i].getTextureName() + texture_number, i);
        }
        vertex_array_.bind();
        glDrawElements(GL_TRIANGLES, indices_.size(), GL_UNSIGNED_INT, 0);
        vertex_array_.unbind();

    }
}
