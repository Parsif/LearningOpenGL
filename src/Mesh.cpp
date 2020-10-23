#include "Mesh.h"

#include <utility>

namespace opengl
{
    Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures) :
        vertices_(std::move(vertices)), indices_(std::move(indices)), textures_(std::move(textures))
    {

    }

}
