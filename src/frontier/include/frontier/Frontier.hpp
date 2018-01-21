#pragma once

#include <frontier/SDLApplication.hpp>

#include <memory>

#include <texture_manager/TextureManager.hpp>

namespace frontier {

class Frontier : public SDLApplication {
public:
    Frontier(std::unique_ptr<TextureManager> textureManager);
    ~Frontier() override = default;

    int exec() override;
};

} // namespace frontier
