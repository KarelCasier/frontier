#include <memory>

#include <frontier/Frontier.hpp>
#include <frontier/StateMachine.hpp>

using namespace frontier;

int main(int /* argc */, char* /*argv*/ [])
{
    auto app = std::make_unique<Frontier>();
    return app->exec();
}
