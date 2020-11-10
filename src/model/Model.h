#pragma once

#include "FileTexture.h"
#include "ShaderProgram.h"
#include "Mesh.h"

#include <vector>

#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace opengl
{
    class Model
    {
    public:
        Model(const std::string &path);
        void render(const ShaderProgram &shader_program);

    private:
        std::vector<Mesh> m_meshes;
        std::vector<ModelTexture> m_loaded_textures;
        std::string m_directory;
    private:
        void loadModel(const std::string &path);
        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
        [[nodiscard]] std::vector<ModelTexture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, TextureType texture_type);
        [[nodiscard]] static unsigned int loadTextureFromFile(const std::string &path);
    };
}
