#pragma once

namespace opengl
{
    class VertexArray
    {
    public:
        VertexArray();
        ~VertexArray();
        void bind() const;
        void unbind() const;

    private:
        unsigned int id_;
    };

}


