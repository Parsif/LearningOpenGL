#include "FileTexture.h"

#include <GL/glew.h>

#include "std_image.h"

namespace opengl
{

    FileTexture::FileTexture(const std::string &texture_path)
    {
        stbi_set_flip_vertically_on_load(1);
        image_buffer_ = stbi_load(texture_path.c_str(), &width_, &height_, &BPP_, 4);

        glGenTextures(1, &id_);
        glBindTexture(GL_TEXTURE_2D, id_);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width_, height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_buffer_);
        const float kBorderColor[] = {1.f, 1.f, 0.f, 1.f};
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, kBorderColor);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);

        if(image_buffer_) stbi_image_free(image_buffer_);
    }

    void FileTexture::bind(unsigned int slot) const
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, id_);
    }

    void FileTexture::unBind() const
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    FileTexture::~FileTexture()
    {
        glDeleteTextures(1, &id_);
    }




}