#include <graphics/TextureManager.hpp>

#include <graphics/Util.hpp>
#include <SDL2_image/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <log/log.hpp>
#include <string>

namespace {

} // namespace

namespace frontier {

TextureManager::TextureManager(SDL_Renderer* renderer)
: _renderer{std::move(renderer)}
{
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
}

TextureManager::~TextureManager()
{
    purgeTextures();
    IMG_Quit();
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
        auto texture = SDL_CreateTextureFromSurface(_renderer, surface);
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
