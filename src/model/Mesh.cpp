#include "Mesh.h"

namespace opengl
{
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wint-to-void-pointer-cast"
    Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<ModelTexture> textures) :
            vertices_(std::move(vertices)), indices_(std::move(indices)), textures_(std::move(textures))
    {
        vertex_array_.bind();
        vertex_buffer_ = std::make_unique<VertexBuffer>(vertices_.data(), vertices_.size() * sizeof(decltype (vertices_)::value_type));
        index_buffer_ = std::make_unique<IndexBuffer>(indices_.data(), indices_.size() * sizeof(decltype (indices_)::value_type));

        BufferLayout layout = {
                {ShaderDataType::Float3},
                {ShaderDataType::Float3},
                {ShaderDataType::Float2}
        };

        size_t i = 0;
        for(auto&& attribute : layout)
        {
            glEnableVertexAttribArray(i);
            glVertexAttribPointer(i, attribute.GetComponentCount(), GL_FLOAT, GL_FALSE, layout.getStride(), (const void*)attribute.Offset);
            ++i;
        }
        vertex_array_.unbind();
    }
#pragma clang diagnostic pop

    void Mesh::render(const ShaderProgram &shader_program)
    {
        unsigned int diffuse_counter = 0;
        unsigned int specular_counter = 0;

        for (unsigned int i = 0; i < textures_.size(); ++i)
        {
            textures_[i].bind(i);
            std::string texture_number;
            if(textures_[i].getTextureType() == TextureType::Diffuse)
                texture_number = std::to_string(diffuse_counter++);
            else if(textures_[i].getTextureType() == TextureType::Diffuse)
                texture_number = std::to_string(specular_counter++);
            shader_program.uniform1i("u_material." + textures_[i].getStringType() + texture_number, i);
        }
        vertex_array_.bind();
        glDrawElements(GL_TRIANGLES, indices_.size(), GL_UNSIGNED_INT, 0);
        vertex_array_.unbind();
    }
}
