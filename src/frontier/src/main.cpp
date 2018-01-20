#include <memory>

#include <frontier/SDLApplication.hpp>

using frontier::SDLApplication;

int main(int /* argc */, char* /*argv*/ [])
{
    auto app = std::make_unique<SDLApplication>();
    app->init();
    return app->exec();
}
