#ifndef LEARNINGOPENGL_TEXTURE_H
#define LEARNINGOPENGL_TEXTURE_H

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
        Texture(const std::string &texture_path);
        ~Texture();

        void Bind(unsigned int slot = 0) const;
        void UnBind() const;
    };
}


#endif //LEARNINGOPENGL_TEXTURE_H
