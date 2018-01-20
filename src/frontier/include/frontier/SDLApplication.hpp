#include <SDL2/SDL.h>

namespace frontier {

class SDLApplication {
public:
    SDLApplication();
    ~SDLApplication();

    int init();
    int exec();

private:
};

} // namespace frontier
