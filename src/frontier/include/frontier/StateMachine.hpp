#pragma once

#include <memory>
#include <chrono>

#include "IStateMachine.hpp"

namespace frontier {

class StateMachine : public IStateMachine {
public:
    StateMachine();
    ~StateMachine() override;

    /// @name IStateMachine Overrides
    /// @{
    void push(std::shared_ptr<IState> state, bool immediate = false) override;
    void pop(bool immediate = false) override;
    void replace(std::shared_ptr<IState> state, bool immediate = false) override;
    void clear() override;
    void update(std::chrono::milliseconds delta) override;
    void render() override;
    void handleEvent(const SDL_Event& event) override;
    bool empty() const override;
    /// @}

private:
    class Impl;
    std::shared_ptr<Impl> _impl;
};

} // namespace frontier
