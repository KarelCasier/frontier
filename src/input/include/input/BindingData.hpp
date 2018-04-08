#pragma once

#include <SDL2/SDL_keycode.h>
#include <bitset>
#include <input/Util.hpp>

namespace frontier {

/// Button states
enum ButtonState {
    RELEASED,
    PRESSED,
};

/// Mouse buttons
enum MouseButton {
    LEFT,
    MIDDLE,
    RIGHT,
    NUM_BUTTONS,
};

/// Keyboard modifiers
enum Modifier {
    CTRL,
    SHIFT,
    ALT,
    NUM_MODIFIERS,
};

using ModifierBitset = std::bitset<Modifier::NUM_MODIFIERS>;
using MouseButtonBitset = std::bitset<MouseButton::NUM_BUTTONS>;

/// Data for keyboard bindings
/// Note: this is hashasble
struct KeyboardBindingData {
    SDL_Keycode key;
    ButtonState state{ButtonState::PRESSED};
    ModifierBitset modifiers{};

    bool operator==(const KeyboardBindingData& rhs) const
    {
        return key == rhs.key && state == rhs.state && modifiers == rhs.modifiers;
    }
};

/// Data for mouse button bindings
/// Note: this is hashasble
struct MouseButtonBindingData {
    MouseButton button{MouseButton::LEFT};
    ButtonState state{ButtonState::PRESSED};

    bool operator==(const MouseButtonBindingData& rhs) const { return button == rhs.button && state == rhs.state; }
};

/// Data for mouse motion bindings
/// Note: this is hashasble
struct MouseMotionBindingData {
    MouseButtonBitset buttons{};

    bool operator==(const MouseMotionBindingData& rhs) const { return buttons == rhs.buttons; }
};

} // namespace frontier

namespace std {

template <>
struct hash<frontier::KeyboardBindingData> {
    std::size_t operator()(const frontier::KeyboardBindingData& data) const
    {
        std::size_t h{0};
        hash_combine(h, hash<SDL_Keycode>()(data.key),
                     hash<std::underlying_type<frontier::ButtonState>::type>()(
                         static_cast<std::underlying_type<frontier::ButtonState>::type>(data.state)),
                     hash<frontier::ModifierBitset>()(data.modifiers));
        return h;
    }
};

template <>
struct hash<frontier::MouseButtonBindingData> {
    std::size_t operator()(const frontier::MouseButtonBindingData& data) const
    {
        std::size_t h{0};
        hash_combine(h,
                     hash<std::underlying_type<frontier::MouseButton>::type>()(
                         static_cast<std::underlying_type<frontier::MouseButton>::type>(data.button)),
                     hash<std::underlying_type<frontier::ButtonState>::type>()(
                         static_cast<std::underlying_type<frontier::ButtonState>::type>(data.state)));
        return h;
    }
};

template <>
struct hash<frontier::MouseMotionBindingData> {
    std::size_t operator()(const frontier::MouseMotionBindingData& data) const
    {
        std::size_t h{0};
        hash_combine(h, hash<frontier::MouseButtonBitset>()(data.buttons));
        return h;
    }
};

} // namespace std
