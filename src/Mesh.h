#ifndef LEARNINGOPENGL_MESH_H
#define LEARNINGOPENGL_MESH_H

#include "global.h"
#include "buffers/VertexArray.h"
#include "buffers/VertexBuffer.h"
#include "buffers/IndexBuffer.h"
#include "ShaderProgram.h"

#include <glm/glm.hpp>

#include <string>
#include <vector>

namespace opengl
{
    struct Vertex
    {
        glm::vec3 position, normal, tex_coords;
    };

    struct Texture
    {
        unsigned int id;
        TextureType texture_type;
    };

    class Mesh
    {
    private:
        VertexArray vertex_array_;
        VertexBuffer vertex_buffer_;
        IndexBuffer index_buffer_;

        std::vector<Vertex> vertices_;
        std::vector<unsigned int> indices_;
        std::vector<Texture> textures_;

    public:
        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
        void render(const ShaderProgram &shader_program);
    };
}


#endif //LEARNINGOPENGL_MESH_H
