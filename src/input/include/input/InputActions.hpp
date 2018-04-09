#pragma once

#include <string>

namespace frontier {

using namespace std::string_literals;

/// Built in mouse events
const auto LeftClick = "LeftClick"s;
const auto MiddleClick = "MiddleClick"s;
const auto RightClick = "RightClick"s;
const auto MouseMotion = "MouseMotion"s;
const auto MouseMotionLeft = "MouseMotionLeft"s;
const auto MouseMotionMiddle = "MouseMotionMiddle"s;
const auto MouseMotionRight = "MouseMotionRight"s;

/// Built in mouse axis events
/// TODO: add axis support
// const auto MouseMoveXAxis = "MouseMoveX"s;
// const auto MouseMoveYAxis = "MouseMoveY"s;
/// TODO: add joystick support
// const auto JoystickXAxis = "JoystickX"s;
// const auto JoystickYAxis = "JoystickY"s;

} // namespace frontier
