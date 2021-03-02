#include <core/system_providers/texture_loader_system_provider.h>
#include <core/systems/texture_loader_system.h>

namespace Vultr
{
void TextureLoaderSystemProvider::OnCreateEntity(Entity entity)
{
    TextureLoaderSystem::OnCreateEntity(entity);
}

void TextureLoaderSystemProvider::OnDestroyEntity(Entity entity)
{
}

Texture *TextureLoaderSystemProvider::GetTexture(const std::string &texture)
{
    if (isLoaded(texture))
    {
        return textures[texture];
    }
    else
    {
        return nullptr;
    }
}

bool TextureLoaderSystemProvider::isLoaded(const std::string &texture)
{
    return textures.find(texture) != textures.end();
}
} // namespace Vultr