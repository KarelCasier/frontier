#pragma once

#include <tinyxml2.h>
#include <string>
#include <navigation/NavMesh.hpp>

namespace frontier {

class LevelNavParser {
public:
    LevelNavParser();

    std::shared_ptr<NavMesh> parse(const std::string& file);

private:
    std::shared_ptr<NavMesh> _navMesh;
};

} // namespace frontier
