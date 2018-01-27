#pragma once

#include <frontier/SDLApplication.hpp>

#include <chrono>
#include <memory>

#include <frontier/states/IStateMachine.hpp>

namespace frontier {

class Frontier : public SDLApplication {
public:
    Frontier();
    ~Frontier() override = default;

    int exec() override;
private:
    void quit();
    bool handleGlobalEvent(const SDL_Event& event);

    std::unique_ptr<IStateMachine> _stateMachine;
};

} // namespace frontier
