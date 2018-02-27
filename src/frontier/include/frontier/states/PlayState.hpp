#pragma once

#include "IState.hpp"

#include <frontier/World.hpp>
#include <input/BindingContext.hpp>

namespace frontier {

class PlayState : public IState {
public:
    PlayState(std::shared_ptr<TextureManager> textureManager, std::shared_ptr<InputManager> inputManager);
    ~PlayState() override;

    /// @name IState overrides
    /// @{
    void onEnter() override;
    void onExit() override;
    void update(std::chrono::milliseconds delta) override;
    void render() override;
    void handleEvent(const SDL_Event& event) override;
    /// @}
private:
    std::shared_ptr<TextureManager> _textureManager;
    std::shared_ptr<InputManager> _inputManager;
    std::shared_ptr<BindingContext> _bindingContext;
    World _world;
};

}
