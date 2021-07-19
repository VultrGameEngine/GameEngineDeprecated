#include <gui/materials/default_gui_material.h>
#include <gui/utils/opengl.h>

using namespace Vultr;

IMGUI::DefaultGUIMaterial *IMGUI::new_gui_material(Context *c, Color color, Texture texture)
{
    auto *mat = new DefaultGUIMaterial();
    mat->shader = !is_valid_texture(texture) ? c->renderer.default_gui_shader : c->renderer.texture_gui_shader;
    mat->texture = texture;
    mat->color = color;
    return mat;
}

void IMGUI::DefaultGUIMaterial::bind()
{
    shader->Bind();
    shader->SetUniform4f("color", gl_get_color(color));
    if (is_valid_texture(texture))
    {
        bind_texture(texture, GL_TEXTURE0);
        shader->SetUniform1i("tex", 0);
    }
}
