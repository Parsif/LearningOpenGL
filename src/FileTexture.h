#pragma once

#include "pch.h"
#include "global.h"

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

