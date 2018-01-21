#include <texture_manager/TextureManager.hpp>

#include <iostream>
#include <string>
#include <SDL2_image/SDL_image.h>
#include <log/log.hpp>

namespace {

#ifdef _WIN32
constexpr char PATH_SEP = '\\';
#else
constexpr char PATH_SEP = '/';
#endif

/*
 * Get the resource path for resources located in assets/subDir
 * It's assumed the project directory is structured like:
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
            //Logger(LOG_ERROR) << "Error getting resource path: " << SDL_GetError();
            return "";
        }
        // We replace the last bin/ with res/ to get the the resource path
        size_t pos = baseRes.rfind("bin");
        baseRes = baseRes.substr(0, pos) + "assets" + PATH_SEP;
    }
    // If we want a specific subdirectory path in the resource directory
    // append it to the base path. This would be something like Lessons/res/Lesson0
    return subDir.empty() ? baseRes : baseRes + subDir + PATH_SEP;
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
        auto assetLocation = std::string{getResourcePath() + PATH_SEP + name};
        auto surface = IMG_Load(assetLocation.c_str());
        if (!surface) {
            Logger(LOG_ERROR) << "Failed to load asset from: " << assetLocation;
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
    for (auto& texturePair : _textures) {
        delete texturePair.second;
    }
    _textures.clear();
}

} // namespace frontier
