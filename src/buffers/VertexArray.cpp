#include "VertexArray.h"

#include <GL/glew.h>

#include <iostream>

namespace opengl
{
    VertexArray::VertexArray()
    {
        glGenVertexArrays(1, &m_id);
    }

    void VertexArray::bind() const
    {
        glBindVertexArray(m_id);
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
