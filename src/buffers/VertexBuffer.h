#ifndef LEARNINGOPENGL_VERTEXBUFFER_H
#define LEARNINGOPENGL_VERTEXBUFFER_H


namespace opengl
{
    class VertexBuffer
    {
    private:
        unsigned int id_;
    public:
        explicit VertexBuffer(const void* data, unsigned int size);
        ~VertexBuffer();

        void bind() const;
        void unbind() const;
    };

}


#endif //LEARNINGOPENGL_VERTEXBUFFER_H
