#include "VertexArray.h"

#include <GL/glew.h>

#include <iostream>

namespace opengl
{
    VertexArray::VertexArray()
    {
        glGenVertexArrays(1, &id_);
    }

    void VertexArray::bind() const
    {
        glBindVertexArray(id_);
    }

    void VertexArray::unbind() const
    {
        glBindVertexArray(0);
    }

    VertexArray::~VertexArray()
    {
       // glDeleteVertexArrays(1, &id_);
    }

}
