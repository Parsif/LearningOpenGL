#include "Mesh.h"

namespace opengl
{
    Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<ModelTexture> textures) :
            m_vertices(std::move(vertices)), m_indices(std::move(indices)), m_textures(std::move(textures))
    {
        m_vertex_array.bind();
        m_vertex_buffer = std::make_unique<VertexBuffer>(m_vertices.data(), m_vertices.size() * sizeof(decltype (m_vertices)::value_type));
        m_index_buffer = std::make_unique<IndexBuffer>(m_indices.data(), m_indices.size() * sizeof(decltype (m_indices)::value_type));

        BufferLayout layout = {
                {ShaderDataType::Float3},
                {ShaderDataType::Float3},
                {ShaderDataType::Float2}
        };

        size_t i = 0;
        for(auto&& attribute : layout)
        {
            glEnableVertexAttribArray(i);
            glVertexAttribPointer(i, attribute.GetComponentCount(), GL_FLOAT, GL_FALSE, layout.getStride(), (const void*)attribute.offset);
            ++i;
        }
        m_vertex_array.unbind();
    }

    void Mesh::render(const ShaderProgram &shader_program) const
    {
        unsigned int diffuse_counter = 0;
        unsigned int specular_counter = 0;

        for (unsigned int i = 0; i < m_textures.size(); ++i)
        {
            m_textures[i].bind(i);
            std::string texture_number;
            if(m_textures[i].getTextureType() == TextureType::Diffuse)
                texture_number = std::to_string(diffuse_counter++);
            else if(m_textures[i].getTextureType() == TextureType::Specular)
                texture_number = std::to_string(specular_counter++);
            shader_program.uniform1i("u_material." + m_textures[i].getStringType() + texture_number, i);
        }
        shader_program.uniform1f("u_material.shininess", 64.0f);

        m_vertex_array.bind();
        glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
        m_vertex_array.unbind();
    }
}
