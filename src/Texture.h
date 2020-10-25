#ifndef LEARNINGOPENGL_TEXTURE_H
#define LEARNINGOPENGL_TEXTURE_H

#include "global.h"

#include <string>

namespace opengl
{

    class Texture
    {
    private:
        unsigned int id_;
        unsigned char* image_buffer_ = nullptr;
        int width_ = 0, height_ = 0, BPP_;
        TextureType texture_type_;
        std::string name_;

    public:
        Texture(TextureType texture_type, const std::string &texture_path);
        explicit Texture(const std::string &texture_path);
        ~Texture();

        void bind(unsigned int slot = 0) const;
        void unBind() const;
        [[nodiscard]] inline auto getTextureType() const { return texture_type_; };
        [[nodiscard]] inline auto getTextureName() const { return name_; };
    };
}


#endif //LEARNINGOPENGL_TEXTURE_H
