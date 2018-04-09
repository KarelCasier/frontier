#pragma once

#include <memory>

#include <math/Rectf.hpp>

namespace frontier {

/// Quadtree implementation to hold bounding boxes (as AABBs).
template <typename T>
class QuadTree {
public:
    QuadTree(Rectf bounds, uint8_t maxLevels);

    bool insert(const T& obj, Rectf boundingBox);
    std::vector<T*> collides(Rectf boundingBox);
    void clear();

private:
    std::unique_ptr<QuadTree[4]> _quads;
    std::vector<std::pair<T*, Rectf>> _objects;
    uint8_t _level;
};

} // namespace frontier
