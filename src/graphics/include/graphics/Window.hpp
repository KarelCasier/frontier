#pragma once

#include <string>
#include <mutex>
#include <thread>
#include <vector>
#include <SDL2/SDL.h>

#include <graphics/IRenderTarget.hpp>
#include <math/Vector2.hpp>

namespace frontier {

class IRenderable;

class Window : public IRenderTarget {
public:
    Window(const std::string& title, int32_t x, int32_t y, int32_t width, int32_t height);
    ~Window();

    /// @name IRenderTarget overrides
    /// @{
    void preRender() override;
    void postRender() override;
    void render(const TextureRef* texture,
                const Recti& srcRect,
                const Recti& destRect,
                const double rotation = 0.0,
                const std::optional<Vector2i> origin = {}) override;
    void render(const Camera& camera,
                const TextureRef* texture,
                const Recti& srcRect,
                const Recti& destRect,
                const double rotation = 0.0,
                const std::optional<Vector2i> origin = {}) override;
    void render(IRenderable& renderable) override;
    /// @}

    /// Get the position of the window.
    Vector2i position() const;

    /// Get the size of the window.
    Vector2i size() const;

    /// Get the window id.
    uint32_t id() const;

    /// Get the focused state.
    bool focused() const;

    /// Get the shown state.
    bool shown() const;

    /// Get the closed state.
    bool closed() const;

    /// Internally handle a window event.
    void handleWindowEvent(SDL_Event& event);

    /// Get the underlying SDL_Window
    SDL_Window* getSDLWindow() const;

    /// Get the underlying SDL_Renderer
    SDL_Renderer* getSDLRenderer() const;

private:
    using StateLock = std::lock_guard<std::mutex>;

    SDL_Window* _window{nullptr};
    SDL_Renderer* _renderer{nullptr};

    uint32_t _id;
    bool _focused{false};
    bool _shown{false};
    bool _closed{false};
    std::vector<SDL_Event> _events;

    std::thread _eventThread;
    std::mutex _eventMutex;
};

} // namespace frontier
