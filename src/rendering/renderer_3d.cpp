#include "../../include/rendering/renderer_3d.h"
#include "../../include/core/components/shader_component.h"
#include "../../include/rendering/models/vertex.h"

namespace Renderer {

Renderer3D::Renderer3D() {}

Renderer3D::~Renderer3D() {}

bool Renderer3D::Register(Entity entity) {
  ShaderComponent &shader_component =
      World::GetComponent<ShaderComponent>(entity);

  if (shader_component.shader == 0) {
    return false;
  }

  // Create a shader abstraction
  Shader *shader = new Shader(shader_component.shader);

  // If we don't have a render group for the shader that this entity requires,
  // create one
  if (render_groups.find(shader_component.shader) == render_groups.end()) {
    render_groups[shader->GetID()] = new RenderGroup(shader);
  }

  // Register the entity to the render group
  render_groups[shader->GetID()]->RegisterEntity(entity);

  // Successfully added the render group
  return true;
}

void Renderer3D::Update(RenderContext context) {
  if (render_groups.size() == 0)
    return;
  for (const auto &[shader_id, group] : render_groups) {
    if (group != nullptr)
      group->Render(context);
  }
}

void Renderer3D::Flush() {
  for (const auto &[shader_id, group] : render_groups) {
    delete group;
  }
}

} // namespace Renderer