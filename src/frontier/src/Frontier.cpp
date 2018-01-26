#include <frontier/Frontier.hpp>

#include <frontier/PlayState.hpp>
#include <log/log.hpp>

namespace {

using namespace std::chrono;
using namespace std::chrono_literals;

static constexpr auto windowTitle{"Frontier"};
static constexpr auto WINDOW_WIDTH{800};
static constexpr auto WINDOW_HEIGHT{600};
static constexpr auto timeStep{16ms};
static constexpr auto framesPerSecond{60};
static constexpr auto timePerFrame{1s / framesPerSecond};
// Used to determine if the application was paused externally (ie. breakpoint).
static constexpr auto resetTimeDeltaThreshhold{1s};

} // namespace

namespace frontier {

Frontier::Frontier(std::unique_ptr<IStateMachine> stateMachine)
: SDLApplication(
      windowTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN)
, _stateMachine{std::move(stateMachine)}
{
}

int Frontier::exec()
{
    _stateMachine->push(std::make_shared<PlayState>(), true);

    SDL_Event event;

    auto now = steady_clock::now();
    auto last_update = steady_clock::now();
    auto lag = 0ns;

    auto frame = 0u;
    auto last_frame = steady_clock::now();

    while (!_stateMachine->empty()) {
        now = steady_clock::now();
        auto delta = now - last_update;
        lag += delta;

        while (lag > timeStep) {
            while (SDL_PollEvent(&event) != 0) {
                if (!handleGlobalEvent(event)) {
                    _stateMachine->handleEvent(event);
                }
            }
            _stateMachine->update(timeStep);

            lag -= timeStep;

            // Reset lag if game was externally paused for too long.
            if (lag > resetTimeDeltaThreshhold) {
                LOGD << "Lag reset";
                lag = 0s;
            }
        }
        last_update = now;

        if (now - last_frame > timePerFrame) {
            _stateMachine->render();
            last_frame = now;
            frame++;
        }
    }

    return 0;
}

void Frontier::quit()
{
    LOGD << "Clearing state machine (exiting)";
    _stateMachine->clear();
}

bool Frontier::handleGlobalEvent(const SDL_Event& event)
{
    auto handled{false};
    switch (event.type) {
    case SDL_QUIT:
        quit();
        handled = true;
        break;
    case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_ESCAPE) {
            quit();
        }
        handled = true;
        break;
    default:
        break;
    }
    return handled;
}

} // namespace frontier
