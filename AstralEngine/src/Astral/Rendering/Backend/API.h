#pragma once
#include "Common.h"


namespace Astral::Render {

    // ========================================== Vertices ==========================================

    enum class AttributeFormat {
        Float,
        Double,
        Int,
        UInt,
        Bool
    };

    struct VertexAttribute {
        uint32_t location;
        uint32_t binding;
        AttributeFormat format;
        uint32_t components;  // length of 1 for non-array data
        size_t offset;
        bool normalized;
    };

    struct VertexBinding {
        uint32_t location;
        uint32_t divisor;
    };

    struct VertexLayout {
        std::vector<VertexAttribute> attributes;
        std::vector<VertexBinding> bindings;
    };

    namespace Attr {

        template <const AttributeFormat format>
        struct Scalar {
            inline static VertexAttribute Layout(uint32_t location, uint32_t binding, uint32_t offset, bool normalized = false) {
                return { location, binding, format, 1, offset, normalized };
            }
        };

        template <const AttributeFormat format, const size_t components>
        struct Vector {
            inline static VertexAttribute Layout(uint32_t location, uint32_t binding, uint32_t offset, bool normalized = false) {
                return { location, binding, format, components, offset, normalized };
            }
        };

        // Scalars
        using Float = Scalar<AttributeFormat::Float>;
        using Double = Scalar<AttributeFormat::Double>;
        using Int = Scalar<AttributeFormat::Int>;
        using UInt = Scalar<AttributeFormat::UInt>;
        using Bool = Scalar<AttributeFormat::Bool>;

        // Vectors
        using Vec2 = Vector<AttributeFormat::Float, 2>;
        using Vec3 = Vector<AttributeFormat::Float, 3>;
        using Vec4 = Vector<AttributeFormat::Float, 4>;
        using DVec2 = Vector<AttributeFormat::Double, 2>;
        using DVec3 = Vector<AttributeFormat::Double, 3>;
        using DVec4 = Vector<AttributeFormat::Double, 4>;
        using IVec2 = Vector<AttributeFormat::Int, 2>;
        using IVec3 = Vector<AttributeFormat::Int, 3>;
        using IVec4 = Vector<AttributeFormat::Int, 4>;
        using UVec2 = Vector<AttributeFormat::UInt, 2>;
        using UVec3 = Vector<AttributeFormat::UInt, 3>;
        using UVec4 = Vector<AttributeFormat::UInt, 4>;
        using BVec2 = Vector<AttributeFormat::Bool, 2>;
        using BVec3 = Vector<AttributeFormat::Bool, 3>;
        using BVec4 = Vector<AttributeFormat::Bool, 4>;
    }


    // ========================================== Abstract ==========================================

    class IResource {
    public:
        virtual ~IResource() = 0;
    };
    inline IResource::~IResource() = default;

    class IBindable {
    public:
        virtual void Bind(uint32_t binding_slot) const = 0;
    };

    class IShader;

    class IBinding {
    public:
        virtual void Bind(IShader* shader) const = 0;
    };


    // ======================================== Vertex Buffer ========================================

    class IVertexBuffer : public IBindable, public IResource {
    public:
        virtual void Upload(const void* data, size_t vertex_count, size_t vertex_offset = 0) const = 0;
        virtual size_t Length() const = 0;
        virtual void Bind(uint32_t binding_slot) const = 0;
    };

    class IVertexBufferBinding : public IBinding {
    public:
        virtual void Bind(IShader* shader) const = 0;
    };


    // ======================================= Uniform Buffer =======================================

    class IUniformBuffer : public IBindable, public IResource {
    public:
        virtual void Upload(const void* data) const = 0;
        virtual void Bind(uint32_t binding_slot) const = 0;
    };

    class IUniformBufferBinding : public IBinding {
    public:
        virtual void Bind(IShader* shader) const = 0;
    };


    // =========================================== Texture ===========================================

    class ITexture : public IBindable, public IResource {
    public:
        virtual void Upload(const void* img_data, size_t texel_count_x, size_t texel_count_y, size_t texel_offset_x = 0, size_t texel_offset_y = 0) const = 0;
        virtual size_t Width() const = 0;
        virtual size_t Height() const = 0;
        virtual void Bind(uint32_t binding_slot) const = 0;
    };

    class ITextureBinding : public IBinding {
    public:
        virtual void Bind(IShader* shader) const = 0;
    };


    // ======================================== Index Buffer ========================================

    class IIndexBuffer : public IResource {
    public:
        virtual void Upload(const void* data, size_t index_count, size_t index_offset = 0) const = 0;
        virtual size_t Length() const = 0;
    };
    

    // =========================================== Shader ===========================================

    class IShader : public IResource {
    public:
        virtual ~IShader() = 0;
    };
    inline IShader::~IShader() = default;


    // ============================================= API =============================================

    class IGraphicsAPI {
    public:
        // Setup
        virtual void Setup() = 0;
        virtual void SetActiveFrameBuffer(uint32_t id) = 0;
        virtual void SetViewport(size_t frame_width, size_t frame_height) = 0;
        virtual void Clear(const glm::vec4& color) = 0;

        // Resources
        virtual Box<IVertexBuffer> CreateVertexBuffer(size_t length, size_t vertex_stride) = 0;
        virtual Box<IUniformBuffer> CreateUniformBuffer(size_t buffer_stride) = 0;
        virtual Box<ITexture> CreateTexture(size_t width, size_t height) = 0;
        virtual Box<IVertexBufferBinding> CreateVertexBufferBinding(uint32_t binding_slot, IVertexBuffer* resource) = 0;
        virtual Box<IUniformBufferBinding> CreateUniformBufferBinding(uint32_t binding_slot, IUniformBuffer* resource) = 0;
        virtual Box<ITextureBinding> CreateTextureBinding(uint32_t binding_slot, ITexture* resource) = 0;
        virtual Box<IIndexBuffer> CreateIndexBuffer(size_t length) = 0;
        virtual Box<IShader> CreateShader(VertexLayout interface, const std::string& vertex_src, const std::string& fragment_src) = 0;

        // Rendering
        virtual void Draw(IShader* shader, std::span<IBinding*> bindings, size_t first_drawn_vertex, size_t drawn_vertex_count) = 0;
        virtual void DrawIndexed(IShader* shader, std::span<IBinding*> bindings, IIndexBuffer* indices, size_t first_drawn_index, size_t drawn_index_count) = 0;
    };
}