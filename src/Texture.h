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

    public:
        Texture() = default;
        explicit Texture(const std::string &texture_path);
        ~Texture();

        void bind(unsigned int slot = 0) const;
        void unBind() const;

        TextureType texture_type_;
        std::string name_;
    };
}


#endif //LEARNINGOPENGL_TEXTURE_H
