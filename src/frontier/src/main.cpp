#include <memory>

#include <frontier/Frontier.hpp>
#include <frontier/states/StateMachine.hpp>

using namespace frontier;

int main(int /* argc */, char* /*argv*/ [])
{
    auto app = std::make_unique<Frontier>();
    return app->exec();
}
