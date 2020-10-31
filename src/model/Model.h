#ifndef LEARNINGOPENGL_MODEL_H
#define LEARNINGOPENGL_MODEL_H

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
    private:
        std::vector<Mesh> meshes_;
        std::string directory_;
    private:
        void loadModel(const std::string &path);
        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
        [[nodiscard]] std::vector<ModelTexture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, TextureType texture_type);
        [[nodiscard]] static unsigned int loadTextureFromFile(const std::string &path);
    public:
        explicit Model(const std::string &path);
        void render(const ShaderProgram &shader_program);
    };
}


#endif //LEARNINGOPENGL_MODEL_H
