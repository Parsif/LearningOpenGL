#ifndef LEARNINGOPENGL_MESH_H
#define LEARNINGOPENGL_MESH_H

#include "global.h"
#include "buffers/VertexArray.h"
#include "buffers/VertexBuffer.h"
#include "buffers/IndexBuffer.h"
#include "ShaderProgram.h"
#include "FileTexture.h"

#include <glm/glm.hpp>

#include <string>
#include <vector>
#include <optional>

namespace opengl
{
    struct Vertex
    {
        glm::vec3 position, normal;
        glm::vec2 tex_coords;
        [[nodiscard]] static inline unsigned int getNormalOffset() {return 3 * sizeof(float);}
        [[nodiscard]] static inline unsigned int getTexCoordOffset() {return getNormalOffset() + 3 * sizeof(float); }
    };

    struct ModelTexture
    {
        unsigned int id;
        std::string name;
        TextureType texture_type;
    };

    class Mesh
    {
    private:
        VertexArray vertex_array_;
        std::optional<VertexBuffer> vertex_buffer_;
        std::optional<IndexBuffer> index_buffer_;

        std::vector<Vertex> vertices_;
        std::vector<unsigned int> indices_;
        std::vector<ModelTexture> textures_;

    public:
        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<ModelTexture> textures);
        void render(const ShaderProgram &shader_program);
    };
}


#endif //LEARNINGOPENGL_MESH_H
