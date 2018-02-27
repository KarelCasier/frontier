#pragma once

#include <input/BindingData.hpp>
#include <string>

namespace frontier {

/// An input action event
struct ActionEvent {
    std::string action;
};

/// An input axis event
struct AxisEvent {
    std::string action;
    float val;
};

/// A input mouse event
struct MouseEvent {
    std::string action;
    int x;
    int y;
};

} // namespace frontier
