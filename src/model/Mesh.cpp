#include "Mesh.h"

namespace opengl
{
    Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<ModelTexture> textures) :
            vertices_(std::move(vertices)), indices_(std::move(indices)), textures_(std::move(textures))
    {
        vertex_array_.bind();
        vertex_buffer_ = std::make_unique<VertexBuffer>(vertices.data(), vertices.size() * sizeof(decltype (vertices)::value_type));
        index_buffer_ = std::make_unique<IndexBuffer>(indices.data(), indices.size() * sizeof(decltype (vertices)::value_type));
        vertex_buffer_->bind();
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
        unsigned int diffuse_counter = 0;
        unsigned int specular_counter = 0;

        for (unsigned int i = 0; i < textures_.size(); ++i)
        {
            textures_[i].bind(i);
            std::string texture_number;
            if(textures_[i].texture_type == TextureType::diffuse)
                texture_number = std::to_string(diffuse_counter++);
            else if(textures_[i].texture_type == TextureType::diffuse)
                texture_number = std::to_string(specular_counter++);
            shader_program.uniform1i("u_material." + textures_[i].name + texture_number, i);
        }
        shader_program.UseShaderProgram();
        vertex_array_.bind();
        glDrawElements(GL_TRIANGLES, indices_.size(), GL_UNSIGNED_INT, 0);
        vertex_array_.unbind();

    }
}
