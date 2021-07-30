#include <rendering/types/uniform_buffer.h>

namespace Vultr
{
    bool is_valid_uniform_buffer(const UniformBuffer &ubo)
    {
        return ubo.id != 0;
    }

    UniformBuffer invalid_uniform_buffer()
    {
        return {};
    }

    UniformBuffer new_uniform_buffer(const char *label, u16 binding_point, size_t size)
    {
        UniformBuffer ubo;

        ubo.label = static_cast<char *>(malloc(sizeof(char) * strlen(label)));
        strcpy(ubo.label, label);

        ubo.binding_point = binding_point;

        glGenBuffers(1, &ubo.id);
        bind_uniform_buffer(ubo);
        glBufferData(GL_UNIFORM_BUFFER, size, nullptr, GL_STREAM_DRAW);
        glBindBufferBase(GL_UNIFORM_BUFFER, ubo.binding_point, ubo.id);

        return ubo;
    }

    void delete_uniform_buffer(const UniformBuffer &ubo)
    {
        assert(is_valid_uniform_buffer(ubo) && "Invalid uniform buffer object!");

        bind_uniform_buffer(ubo);

        free(ubo.label);
    }

    void bind_uniform_buffer(const UniformBuffer &ubo)
    {
        glBindBuffer(GL_UNIFORM_BUFFER, ubo.id);
    }

    void unbind_all_uniform_buffers()
    {
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }

    void attach_shader_uniform_buffer(Shader shader, UniformBuffer &ubo)
    {
        // Get the shader uniform block
        s32 uniform_block_index = glGetUniformBlockIndex(shader, ubo.label);

        if (uniform_block_index == -1)
        {
            fprintf(stderr, "Uniform block index not found %s!", ubo.label);
            return;
        }

        // Bind the block index to our binding point
        glUniformBlockBinding(shader, uniform_block_index, ubo.binding_point);
    }
} // namespace Vultr