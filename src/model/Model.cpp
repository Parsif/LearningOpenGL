#include "Model.h"

#include <assimp/Importer.hpp>
#include <std_image.h>

namespace opengl
{

    Model::Model(const std::string &path)
    {
        loadModel(path);
    }

    void Model::render(const ShaderProgram &shader_program) const
    {
        for(auto&& mesh : m_meshes)
        {
            mesh.render(shader_program);
        }
    }

    void Model::loadModel(const std::string &path)
    {
        Assimp::Importer importer;
        const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

        if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << '\n';
            return;
        }
        m_directory = path.substr(0, path.find_last_of('/'));

        processNode(scene->mRootNode, scene);
    }

    void Model::processNode(aiNode *node, const aiScene *scene)
    {
        for(unsigned int i = 0; i < node->mNumMeshes; i++)
        {
            aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
            m_meshes.push_back(processMesh(mesh, scene));
        }
        // then do the same for each of its children

        for(unsigned int i = 0; i < node->mNumChildren; i++)
        {
            processNode(node->mChildren[i], scene);
        }
    }

    Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene)
    {
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<ModelTexture> textures;

        for(unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            glm::vec3 position(mesh->mVertices[i].x, mesh->mVertices[i].y,  mesh->mVertices[i].z);
            glm::vec3 normals(mesh->mNormals[i].x, mesh->mNormals[i].y,  mesh->mNormals[i].z);
            glm::vec2 tex_coord;
            if(mesh->mTextureCoords[0])
            {
                tex_coord = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
            }
            else
            {
                tex_coord = glm::vec2(0.0f);
            }
            vertices.push_back(Vertex{position, normals, tex_coord});
        }

        for (unsigned int i = 0; i < mesh->mNumFaces; ++i)
        {
            aiFace face = mesh->mFaces[i];
            for (unsigned int j = 0; j < face.mNumIndices; ++j)
            {
                indices.push_back(face.mIndices[j]);
            }
        }

        if(mesh->mMaterialIndex >= 0)
        {
            aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
            auto diffuse_map = loadMaterialTextures(material, aiTextureType_DIFFUSE, TextureType::Diffuse);
            auto specular_map = loadMaterialTextures(material, aiTextureType_SPECULAR, TextureType::Specular);
            textures.insert(textures.end(), diffuse_map.begin(), diffuse_map.end());
            textures.insert(textures.end(), specular_map.begin(), specular_map.end());
        }

        return Mesh(vertices, indices, textures);
    }

    [[nodiscard]] std::vector<ModelTexture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, TextureType texture_type)
    {
        std::vector<ModelTexture> textures;
        for (unsigned int i = 0; i < mat->GetTextureCount(type); ++i)
        {
            aiString texture_name;
            mat->GetTexture(type, i, &texture_name);
            const auto texture_iter = std::find_if (m_loaded_textures.begin(), m_loaded_textures.end(), [texture_name](const ModelTexture& texture){
                return texture.getFilePath() == texture_name.C_Str();
            });
            if(texture_iter == m_loaded_textures.end())
            {
                auto texture = ModelTexture(loadTextureFromFile(m_directory + '/' + texture_name.C_Str()),
                                            texture_name.C_Str(), texture_type);
                m_loaded_textures.emplace_back(texture);
                textures.emplace_back(texture);
            }
            else
            {
                textures.emplace_back(*texture_iter);
            }
        }
        return textures;
    }

    [[nodiscard]] unsigned int Model::loadTextureFromFile(const std::string &path)
    {
        unsigned int texture_id;
        glGenTextures(1, &texture_id);
        int width, height, nrComponents;
        stbi_set_flip_vertically_on_load(true);
        unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrComponents, 0);
        if (!data)
        {
            std::cout << "Texture failed to load at path: " << path << std::endl;
        }

        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, texture_id);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);

        return texture_id;
    }
}

