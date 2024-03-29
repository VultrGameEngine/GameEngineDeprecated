#include <core/systems/font_system.h>
#include <core/system_providers/font_system_provider.h>
#include <helpers/font_importer.h>
#include <engine.hpp>

namespace Vultr::FontSystem
{
    void register_system()
    {
        Signature signature;
        register_global_system<Component>(signature, nullptr, nullptr);
    }

    void init()
    {
        auto &provider = get_provider();
        if (FT_Init_FreeType(&provider.library))
        {
            assert("Could not init the freetype library");
        }
    }

    void preload_font(const FontSource &source)
    {
        auto &provider = get_provider();
        provider.fonts[source.path.string().c_str()] = FontImporter::import_font(source, provider.library);
    }
} // namespace Vultr::FontSystem
