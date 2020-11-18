#pragma once

#include "types.h"

namespace opengl
{
    struct FrameBufferSpecifications
    {
        uint32_t width, height;
        uint32_t samples = 1;
    };

    class FrameBuffer
    {
    public:
        FrameBuffer(const FrameBufferSpecifications& spec);
        ~FrameBuffer();

        void bind() const;
        void unbind() const;

        [[nodiscard]] inline auto getColorAttachmentId() const { return m_color_attachment; }
        [[nodiscard]] inline const auto& getSpecification() const { return m_specifications; }

    private:
        rendererIdType m_id;
        rendererIdType m_color_attachment, m_depth_stencil_attachment;
        FrameBufferSpecifications m_specifications;
    };
}




