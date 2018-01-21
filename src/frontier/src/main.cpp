#include <memory>

#include <frontier/Frontier.hpp>
#include <texture_manager/TextureManager.hpp>

using namespace frontier;

int main(int /* argc */, char* /*argv*/ [])
{
    auto textureManager = std::make_unique<TextureManager>();
    auto app = std::make_unique<Frontier>(std::move(textureManager));
    return app->exec();
}
