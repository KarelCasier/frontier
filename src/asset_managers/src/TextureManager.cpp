#include <texture_manager/TextureManager.hpp>

#include <asset_util/Util.hpp>
#include <SDL2_image/SDL_image.h>
#include <math/Misc.hpp>
#include <cmath>
#include <iostream>
#include <log/log.hpp>
#include <string>

namespace {

} // namespace

namespace frontier {

TextureManager::TextureManager(SDL_Renderer* renderer)
: _renderer{renderer}
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
    auto stringHashFn = std::hash<std::string>{};
    const auto hashId = stringHashFn(name);

    auto textureI = _textures.find(hashId);
    if (textureI == _textures.end()) {
        auto assetLocation = std::string{getResourcePath() + name};
        auto surface = IMG_Load(assetLocation.c_str());
        if (!surface) {
            LOGE << "Failed to load asset from: " << assetLocation;
        }
        auto texture = SDL_CreateTextureFromSurface(_renderer, surface);

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
    }
    _textures.clear();
}

void TextureManager::render(const TextureRef* texture,
                            const SDL_Rect& srcRect,
                            const SDL_Rect& destRect,
                            const double rotation,
                            const SDL_Point* origin)
{
    SDL_RenderCopyEx(_renderer, texture->_texture, &srcRect, &destRect, toDegrees(rotation), origin, SDL_FLIP_NONE);
}

} // namespace frontier
