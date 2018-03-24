#include <graphics/TextureManager.hpp>

#include <string>

#include <graphics/Util.hpp>
#include <graphics/Window.hpp>
#include <log/log.hpp>

#include <SDL2_image/SDL_image.h>
#include <SDL2/SDL.h>

namespace frontier {

/// SDL_image library has global initialization only
class TextureManager::SDL_Image {
public:
    SDL_Image()
    {
        if (instances == 0) {
            IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
        }
        ++instances;
    }
    ~SDL_Image()
    {
        --instances;
        if (instances == 0) {
            IMG_Quit();
        }
    }

private:
    static uint8_t instances;
};

uint8_t TextureManager::SDL_Image::instances = 0;

TextureManager::TextureManager(std::shared_ptr<Window> window)
: _window{std::move(window)}
, _sdlImage{std::make_unique<SDL_Image>()}
{
}

TextureManager::~TextureManager()
{
    purgeTextures();
}

TextureRef* TextureManager::loadTexture(const std::string& name)
{
    const auto hashId = std::hash<std::string>{}(name);
    const auto textureI = _textures.find(hashId);
    if (textureI == _textures.end()) {
        const auto assetLocation = std::string{getResourcePath() + name};
        auto surface = IMG_Load(assetLocation.c_str());
        if (!surface) {
            throw std::runtime_error{"Failed to load asset from: " + assetLocation};
        }
        auto texture = SDL_CreateTextureFromSurface(_window->getSDLRenderer(), surface);
        SDL_FreeSurface(surface);
        auto textureRef = new TextureRef{hashId, name, texture};
        _textures.insert({hashId, textureRef});
        return textureRef;
    }
    return textureI->second;
}

void TextureManager::purgeTextures()
{
    for (auto& [_, textureRef] : _textures) {
        SDL_DestroyTexture(textureRef->_texture);
        delete textureRef;
        textureRef = nullptr;
    }
    _textures.clear();
}

} // namespace frontier
