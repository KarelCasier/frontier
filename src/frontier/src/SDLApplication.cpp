#include <frontier/SDLApplication.hpp>

#include <log/log.hpp>

namespace frontier {

using std::stringstream;

SDLApplication::SDLApplication(const std::string& title, int x, int y, int width, int height)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        const auto err = stringstream{} << "SDL_Init Error: " << SDL_GetError();
        LOGE << err.str();
        throw std::runtime_error(err.str());
    }
    SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" );

    _window = std::make_shared<Window>(title, x, y, width, height);
}

SDLApplication::~SDLApplication()
{
    SDL_Quit();
}

} // namespace frontier
