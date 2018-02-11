#pragma once
#include <vector>
#include <utility>
#include <queue>
#include <unordered_map>
#include <memory>
#include <SDL2/SDL.h>

#include "NavPoly.hpp"

namespace frontier {

template <typename T>
class NavMesh {
public:
    void addPoly(std::shared_ptr<ConvexShape<T>> shape);

    std::vector<Vector2<T>> navigationPath(const Vector2<T>& startPos, const Vector2<T>& targetPos);

private:
    void regenerate();

    std::vector<std::shared_ptr<NavPoly<T>>> _mesh;
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
