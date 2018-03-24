#pragma once

#include <memory>
#include <SDL2/SDL.h>
#include <graphics/Window.hpp>

namespace frontier {

class SDLApplication {
public:
    SDLApplication(const std::string& title, int x, int y, int width, int height);
    virtual ~SDLApplication();

    virtual int exec() = 0;

protected:
    std::shared_ptr<Window> _window;
};

} // namespace frontier
