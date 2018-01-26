#include <memory>

#include <frontier/Frontier.hpp>
#include <frontier/StateMachine.hpp>

using namespace frontier;

int main(int /* argc */, char* /*argv*/ [])
{
    auto stateMachine = std::make_unique<StateMachine>();
    auto app = std::make_unique<Frontier>(std::move(stateMachine));
    return app->exec();
}
