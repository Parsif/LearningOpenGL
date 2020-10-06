#ifndef LEARNINGOPENGL_VERTEXARRAY_H
#define LEARNINGOPENGL_VERTEXARRAY_H

namespace opengl
{
    class VertexArray
    {
    private:
        unsigned int id_;
    public:
        VertexArray();
        ~VertexArray();
        void bind() const;
        void unbind() const;
    };

}



#endif //LEARNINGOPENGL_VERTEXARRAY_H
