#ifndef LEARNINGOPENGL_BUFFER_H
#define LEARNINGOPENGL_BUFFER_H

#include <initializer_list>
#include <vector>
#include <cstdint>

namespace opengl
{
    //////////////////////////////////////////////////
    //VertexBuffer////////////////////////////////////
    //////////////////////////////////////////////////

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

    //////////////////////////////////////////////////
    //IndexBuffer/////////////////////////////////////
    //////////////////////////////////////////////////

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


    //////////////////////////////////////////////////
    //BufferLayout/////////////////////////////////////
    //////////////////////////////////////////////////

    enum class ShaderDataType
    {
        None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
    };

    static size_t ShaderDataTypeSize(ShaderDataType type)
    {
        switch (type)
        {
            case ShaderDataType::Float:    return 4;
            case ShaderDataType::Float2:   return 4 * 2;
            case ShaderDataType::Float3:   return 4 * 3;
            case ShaderDataType::Float4:   return 4 * 4;
            case ShaderDataType::Mat3:     return 4 * 3 * 3;
            case ShaderDataType::Mat4:     return 4 * 4 * 4;
            case ShaderDataType::Int:      return 4;
            case ShaderDataType::Int2:     return 4 * 2;
            case ShaderDataType::Int3:     return 4 * 3;
            case ShaderDataType::Int4:     return 4 * 4;
            case ShaderDataType::Bool:     return 1;
        }

        return 0;
    }

    struct BufferElement
    {
        ShaderDataType Shader_type;
        bool Normalized;
        size_t Size;
        uint32_t Offset;

        BufferElement(ShaderDataType shader_type, bool normalized = false) :
        Shader_type(shader_type), Normalized(normalized), Size(ShaderDataTypeSize(shader_type)){}

        [[nodiscard]] uint32_t GetComponentCount() const
        {
            switch (Shader_type)
            {
                case ShaderDataType::Float:   return 1;
                case ShaderDataType::Float2:  return 2;
                case ShaderDataType::Float3:  return 3;
                case ShaderDataType::Float4:  return 4;
                case ShaderDataType::Mat3:    return 3; // 3* float3
                case ShaderDataType::Mat4:    return 4; // 4* float4
                case ShaderDataType::Int:     return 1;
                case ShaderDataType::Int2:    return 2;
                case ShaderDataType::Int3:    return 3;
                case ShaderDataType::Int4:    return 4;
                case ShaderDataType::Bool:    return 1;
                case ShaderDataType::None:    break;
            }

            return 0;
        }
    };

    class BufferLayout
    {
    private:
        std::vector<BufferElement> elements_;
        uint32_t stride_;

    public:
        BufferLayout(std::initializer_list<BufferElement> buffer_elements) : elements_(buffer_elements)
        {
            size_t offset = 0;
            stride_ = 0;
            for (auto& element : elements_)
            {
                element.Offset = offset;
                offset += element.Size;
                stride_ += element.Size;
            }
        }

        std::vector<BufferElement>::iterator begin() { return elements_.begin(); }
        std::vector<BufferElement>::iterator end() { return elements_.end(); }
        [[nodiscard]] std::vector<BufferElement>::const_iterator begin() const { return elements_.begin(); }
        [[nodiscard]] std::vector<BufferElement>::const_iterator end() const { return elements_.end(); }

        [[nodiscard]] inline auto& getElements() const { return elements_; }
        [[nodiscard]] inline auto getStride() const { return stride_; }
    };

}



#endif //LEARNINGOPENGL_BUFFER_H
