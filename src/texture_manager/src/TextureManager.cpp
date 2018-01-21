#include <texture_manager/TextureManager.hpp>

#include <SDL2_image/SDL_image.h>

namespace frontier {

std::mutex TextureManager::_sdlImageMutex{};
bool TextureManager::_sdlImageInit = false;
uint32_t TextureManager::_count = false;

TextureManager::TextureManager()
{
    StateLock{_sdlImageMutex};
    if (_count == 0) {
        IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
        _sdlImageInit = true;
    }
    _count += 1;
}

TextureManager::~TextureManager()
{
    StateLock{_sdlImageMutex};
    if (_sdlImageInit && _count == 0) {
        IMG_Quit();
    }
}

} // namespace frontier
