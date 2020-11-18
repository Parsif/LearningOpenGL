#pragma once

#include "types.h"

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
        rendererIdType m_id;
    };

}


