#include <graphics/RenderManager.hpp>

#include <cassert>

#include <SDL2/SDL_render.h>

#include <graphics/TextureManager.hpp>
#include <graphics/ISelfRenderable.hpp>
#include <math/Misc.hpp>

namespace frontier {

RenderManager::RenderManager(SDL_Renderer* renderer)
: _renderer{std::move(renderer)}
{
}

void RenderManager::render(const TextureRef* texture,
                           const SDL_Rect& srcRect,
                           const SDL_Rect& destRect,
                           const double rotation,
                           const SDL_Point* origin)
{
    assert(texture);
    SDL_RenderCopyEx(_renderer, texture->texture(), &srcRect, &destRect, toDegrees(rotation), origin, SDL_FLIP_NONE);
}

void RenderManager::render(const Camera& /*camera*/,
                           const TextureRef* /*texture*/,
                           const SDL_Rect& /*srcRect*/,
                           const SDL_Rect& /*destRect*/,
                           const double /*rotation*/,
                           const SDL_Point* /*origin*/)
{
    throw std::logic_error{"Unimplemented"};
    //assert(texture);
    //auto offsetDestRect = SDL_Rect{};
    //const auto cameraBounds = camera.bounds();
    //offsetDestRect.x = cameraBounds.x();
    //offsetDestRect.y = cameraBounds.y();
//
    //offsetDestRect.w = cameraDimensions.x();
    //offsetDestRect.h = cameraDimensions.y();
    //render(texture, srcRect, offsetDestRect, rotation, origin);
}

void RenderManager::render(ISelfRenderable* renderable)
{
    assert(renderable);
    renderable->renderSelf(_renderer);
}

} // namespace frontier
