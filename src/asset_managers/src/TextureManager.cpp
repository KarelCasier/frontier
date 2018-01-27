#include <texture_manager/TextureManager.hpp>

#include <iostream>
#include <string>
#include <SDL2_image/SDL_image.h>
#include <log/log.hpp>

namespace {

using namespace frontier;
using namespace std::string_literals;

#ifdef _WIN32
constexpr auto pathSep = '\\';
#else
constexpr auto pathSep = '/';
#endif

const auto binaryDir = "bin"s;
const auto assetDir = "assets"s;

/*
 * Get the resource path for resources located in assets/subDir
 * It's assumed the project directory is structured as:
 * bin/
 *  binary
 * assets/
 *  subdir1/
 *  subdir2/
 */
std::string getResourcePath(const std::string& subDir = "")
{
    static std::string baseRes;
    if (baseRes.empty()) {
        // SDL_GetBasePath will return NULL if something went wrong in retrieving the path
        char* basePath = SDL_GetBasePath();
        if (basePath) {
            baseRes = basePath;
            SDL_free(basePath);
        } else {
            LOGE << "Error getting resource path: " << SDL_GetError();
            return "";
        }
        size_t pos = baseRes.rfind(binaryDir);
        baseRes = baseRes.substr(0, pos) + "assets" + pathSep;
    }
    return subDir.empty() ? baseRes : baseRes + subDir + pathSep;
}

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

void TextureManager::render(TextureRef* texture, int x, int y, int width, int height)
{
    SDL_Rect src{0, 0, width, height};
    SDL_Rect dest{x, y, width, height};
    SDL_RenderCopyEx(_renderer, texture->_texture, &src, &dest, 0, 0, SDL_FLIP_NONE);
}

} // namespace frontier
