#include <frontier/StateMachine.hpp>

#include <cassert>
#include <stack>
#include <queue>

namespace frontier {

enum class EventID {
    PUSH,
    POP,
    REPLACE,
    CLEAR,
};

struct Event {
    Event(EventID id)
    : id{id}
    {
    }
    Event(EventID id, std::shared_ptr<IState> state)
    : id{id}
    , state{std::move(state)}
    {
    }
    EventID id;
    std::shared_ptr<IState> state;
};

class StateMachine::Impl {
public:
    ~Impl() = default;

    void pushEvent(Event&& event, bool immediate);
    void flushEvents();
    void push(std::shared_ptr<IState> state);
    std::shared_ptr<IState> pop();
    std::shared_ptr<IState> replace(std::shared_ptr<IState> state);
    void clear();
    void update(std::chrono::milliseconds delta);
    void render();
    void handleEvent(const SDL_Event& event);
    bool empty() const;

    std::stack<std::shared_ptr<IState>> _stateStack;
    std::queue<Event> _eventQueue;
};

void StateMachine::Impl::pushEvent(Event&& event, bool immediate)
{
    _eventQueue.push(std::move(event));
    if (immediate) {
        flushEvents();
    }
}

void StateMachine::Impl::push(std::shared_ptr<IState> state)
{
    state->onEnter();
    _stateStack.push(std::move(state));
}

std::shared_ptr<IState> StateMachine::Impl::pop()
{
    auto state = _stateStack.top();
    state->onExit();
    _stateStack.pop();
    return state;
}

std::shared_ptr<IState> StateMachine::Impl::replace(std::shared_ptr<IState> state)
{
    auto old = pop();
    push(state);
    return old;
}

void StateMachine::Impl::clear()
{
    while (!empty()) {
        pop();
    }
}
void StateMachine::Impl::update(std::chrono::milliseconds delta)
{
    flushEvents();
    if (!empty()) {
        _stateStack.top()->update(delta);
    }
}
void StateMachine::Impl::render()
{
    if (!empty()) {
        _stateStack.top()->render();
    }
}
void StateMachine::Impl::handleEvent(const SDL_Event& event)
{
    if (!empty()) {
        _stateStack.top()->handleEvent(event);
    }
}
bool StateMachine::Impl::empty() const
{
    return _stateStack.empty();
}

StateMachine::StateMachine()
: _impl{std::make_unique<Impl>()}
{
}

StateMachine::~StateMachine() {}

void StateMachine::push(std::shared_ptr<IState> state, bool immediate)
{
    assert(state);
    _impl->pushEvent({EventID::PUSH, std::move(state)}, immediate);
}

void StateMachine::pop(bool immediate)
{
    _impl->pushEvent({EventID::PUSH}, immediate);
}

void StateMachine::replace(std::shared_ptr<IState> state, bool immediate)
{
    assert(state);
    _impl->pushEvent({EventID::REPLACE, std::move(state)}, immediate);
}

void StateMachine::clear()
{
    _impl->pushEvent({EventID::CLEAR}, true);
}

void StateMachine::update(std::chrono::milliseconds delta)
{
    _impl->update(delta);
}

void StateMachine::render()
{
    _impl->render();
}

void StateMachine::handleEvent(const SDL_Event& event)
{
    _impl->handleEvent(event);
}

bool StateMachine::empty() const
{
    return _impl->empty();
}

void StateMachine::Impl::flushEvents()
{
    while (!_eventQueue.empty()) {
        auto event = _eventQueue.front();
        _eventQueue.pop();

        switch (event.id) {
        case EventID::PUSH: {
            event.state->onEnter();
            _stateStack.push(std::move(event.state));
            break;
        }
        case EventID::POP: {
            assert(!_stateStack.empty());
            pop()->onExit();
            break;
        }
        case EventID::REPLACE: {
            assert(!_stateStack.empty());
            pop()->onExit();
            event.state->onEnter();
            _stateStack.push(std::move(event.state));
            break;
        }
        case EventID::CLEAR: {
            clear();
            break;
        }
        }
    }
}

} // namespace frontier
