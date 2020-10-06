#ifndef LEARNINGOPENGL_INDEXBUFFER_H
#define LEARNINGOPENGL_INDEXBUFFER_H

namespace opengl
{
    class IndexBuffer
    {
    private:
        unsigned int id_;
    public:
        explicit IndexBuffer(const unsigned int* data, unsigned int size);
        ~IndexBuffer();

        void bind() const;
        void unbind() const;

    };
}

#endif //LEARNINGOPENGL_INDEXBUFFER_H
