#include <navigation/AStar.hpp>

#include <queue>
#include <set>
#include <unordered_map>

namespace {

using namespace frontier;

const auto infeasablePathCost = 99999u;

template <typename T, typename Priority = uint32_t>
struct PriorityQueue {
    typedef std::pair<Priority, T> PQElement;
    std::priority_queue<PQElement, std::vector<PQElement>, std::greater<>> elements;

    inline bool empty() { return elements.empty(); }

    inline void insert(T item, Priority priority) { elements.emplace(priority, item); }

    inline T extract()
    {
        auto top = elements.top().second;
        elements.pop();
        return top;
    }
};

/// VERY simple heuristic that computes the distance between centers.
float heuristic(const NavPoly& a, const NavPoly& b)
{
    return Vector2f{a._shape.center() - b._shape.center()}.lengthSquared();
}

std::vector<const NavPoly*> backtracePath(std::unordered_map<const NavPoly*, const NavPoly*> trace,
                                          const NavPoly* target)
{
    auto path = std::vector<const NavPoly*>{target};
    while (trace[target] != nullptr) {
        target = trace[target];
        path.push_back(target);
    }
    std::reverse(begin(path), end(path));
    return path;
}

} // namespace

namespace frontier {

std::vector<const NavPoly*> AStar::findNavPolyPath(const NavPoly* initial, const NavPoly* target)
{
    std::set<const NavPoly*> closedSet;                       // Set of already checked nodes
    std::set<const NavPoly*> openSet;                         // Set of nodes to check
    PriorityQueue<const NavPoly*> prioritizedOpenSet;         // Prioritized set of nodes to check
    std::unordered_map<const NavPoly*, const NavPoly*> trace; // Most efficient backtrace
    std::unordered_map<const NavPoly*, float> gScore;         // Cost from start along best known path
    std::unordered_map<const NavPoly*, float> fScore;         // Total cost from start to goal through y

    openSet.insert(initial);
    prioritizedOpenSet.insert(initial, 0);

    gScore.emplace(initial, 0);
    fScore.emplace(initial, heuristic(*initial, *target));

    while (!openSet.empty()) {
        auto current = prioritizedOpenSet.extract();
        openSet.erase(current);

        if (current == target) {
            return backtracePath(trace, target);
        }

        closedSet.insert(current);

        for (const auto& [neighbour, _] : current->_neighbours) {
            if (closedSet.find(neighbour) != end(closedSet)) {
                continue; // Already considered
            }

            // Set default score if no score exsits
            gScore.try_emplace(neighbour, infeasablePathCost);

            auto tentativeGScore = gScore[current] + heuristic(*current, *neighbour);

            if (openSet.find(neighbour) == end(openSet)) {
                gScore[neighbour] = tentativeGScore;
                fScore[neighbour] = tentativeGScore + heuristic(*neighbour, *target);
                openSet.emplace(neighbour);
                prioritizedOpenSet.insert(neighbour, fScore[neighbour]);
            } else if (tentativeGScore >= gScore[neighbour]) {
                continue; // Not a better path
            }

            trace[neighbour] = current;
        }
    }

    static_assert(true, "Should not reach this point.");
    return {};
}

} // namespace frontier
