#pragma once

#include <string>
#include <unordered_map>
#include <input/BindingData.hpp>
#include <input/Optional.hpp>

namespace frontier {

/// Class that encapsulates all binding data for a given context
class BindingContext {
public:
    /// Load a binding set from a file
    /// @param file The file to load from
    /// @returns the binding context from the file
    /// @throws runtime_error on parsing failure
    static BindingContext fromFile(const std::string& file);

    /// Saves the binding context to file
    /// @param file The name of the file to save
    /// @returns True if save successful, false otherwise
    bool toFile(const std::string& file);

    /// Add a keyboard action binding to the context
    /// @param action The action the binding triggers
    /// @param bindingData The keyboard binding data
    /// @returns False if the action exists already, true otherwise
    bool addKeyboardActionBinding(std::string action, KeyboardBindingData bindingData);

    /// Add a mouse button action binding to the context
    /// @param action The action the binding triggers
    /// @param bindingData The mouse button binding data
    /// @returns False if the action exists already, true otherwise
    bool addMouseActionBinding(std::string action, MouseButtonBindingData bindingData);

    /// Add a axis binding to the context
    /// @param action The action the binding triggers
    /// @param bindingData The mouse button binding data
    /// @returns False if the action exists already, true otherwise
    bool addMouseMotionBinding(std::string action, MouseMotionBindingData bindingData);

    /// Attempts to map a keyboard binding to an action
    /// @param bindingData The binding data to attempt to match
    /// @return The action if it exists, std::nullopt otherwise
    std::optional<std::string> mapKeyboardBindingToAction(const KeyboardBindingData& bindingData) const;

    /// Attempts to map a mouse binding to an action
    /// @param bindingData The binding data to attempt to match
    /// @return The action if it exists, std::nullopt otherwise
    std::optional<std::string> mapMouseButtonBindingToAction(const MouseButtonBindingData& bindingData) const;

    /// Attempts to map a mouse motion binding to an action
    /// @param bindingData The binding data to attempt to match
    /// @return The action if it exists, std::nullopt otherwise
    std::optional<std::string> mapMouseMotionBindingToAction(const MouseMotionBindingData& bindingData) const;

private:
    std::unordered_map<KeyboardBindingData, std::string> _actionBindings;
    std::unordered_map<MouseButtonBindingData, std::string> _mouseButtonBindings;
    std::unordered_map<MouseMotionBindingData, std::string> _mouseMotionBindings;
};

} // namespace frontier
