#ifndef LEARNINGOPENGL_FILETEXTURE_H
#define LEARNINGOPENGL_FILETEXTURE_H

#include "global.h"

#include <string>

namespace opengl
{

    class FileTexture
    {
    private:
        unsigned int id_;
        unsigned char* image_buffer_ = nullptr;
        int width_ = 0, height_ = 0, BPP_;

    public:
        explicit FileTexture(const std::string &texture_path);
        ~FileTexture();

        void bind(unsigned int slot = 0) const;
        void unBind() const;
    };
}


#endif //LEARNINGOPENGL_FILETEXTURE_H
