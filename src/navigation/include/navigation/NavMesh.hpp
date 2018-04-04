#pragma once

#include <graphics/IRenderable.hpp>

#include <vector>
#include <utility>
#include <queue>
#include <unordered_map>
#include <memory>

#include "NavPoly.hpp"

namespace frontier {

class NavMesh : public IRenderable {
public:
    void addPoly(ConvexShape<float> shape);

    std::vector<Vector2f> navigationPath(const Vector2f& startPos, const Vector2f& targetPos);

    /// @name IRenderable overrides
    /// @{
    void render(IRenderTarget& renderTarget) override;
    /// @}

private:
    void regenerate();

    std::vector<NavPoly> _mesh;
};

template <typename T, typename Number = int>
struct PriorityQueue {
    typedef std::pair<Number, T> PQElement;
    std::priority_queue<PQElement, std::vector<PQElement>, std::greater<PQElement>> elements;

    inline bool empty() { return elements.empty(); }

    inline void add(T item, Number priority) { elements.emplace(priority, item); }

    inline T get()
    {
        T best_item = elements.top().second;
        elements.pop();
        return best_item;
    }
};

} // namespace frontier
