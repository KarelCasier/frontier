#pragma once

#include <mutex>
#include <SDL2/SDL.h>

namespace frontier {

class TextureManager {
public:
    TextureManager();
    ~TextureManager();
private:
    using StateLock = std::unique_lock<std::mutex>;

    static std::mutex _sdlImageMutex;
    static bool _sdlImageInit;
    static uint32_t _count;
};

} // namespace frontier
