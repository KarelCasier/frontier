#include <frontier/SDLApplication.hpp>

namespace frontier {

class Frontier : public SDLApplication {
public:
    Frontier();
    ~Frontier() override = default;

    int exec() override;
};

} // namespace frontier
