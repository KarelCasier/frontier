#pragma once

#include "IState.hpp"

namespace frontier {

class PlayState : public IState {
public:
    PlayState();
    ~PlayState() override;

    /// @name IState overrides
    /// @{
    void onEnter() override;
    void onExit() override;
    void update(std::chrono::milliseconds delta) override;
    void render() override;
    void handleEvent(const SDL_Event& event) override;
    /// @}

};

}
