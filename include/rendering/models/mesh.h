#pragma once
#include <glm/glm.hpp>
#include <helpers/loading_state.h>
#include <rendering/models/index_buffer.h>
#include <rendering/models/shader.h>
#include <rendering/models/vertex.h>
#include <rendering/models/vertex_array.h>
#include <rendering/models/vertex_buffer.h>
#include <vector>

namespace Brick3D
{
class Mesh
{
  public:
    Mesh();
    ~Mesh();

    inline LoadingState GetLoadingState()
    {
        if (vao == nullptr || ibo == nullptr || vbo == nullptr)
            return LoadingState_NotLoaded;
        return LoadingState_Loaded;
    }

    void Init(const std::vector<glm::vec3> &p_positions,
              const std::vector<glm::vec2> &p_uvs,
              const std::vector<glm::vec3> &p_normals,
              const std::vector<unsigned short> &p_indices);

  private:
    // Holds the saved vertices and indices in a buffer cpu side
    std::vector<Vertex> m_vertices;
    std::vector<unsigned short> m_indices;

    // A bunch of required buffers
    VertexArray *vao;
    IndexBuffer *ibo;
    VertexBuffer *vbo;
};
} // namespace Brick3D
