#include <input/BindingContext.hpp>

namespace frontier {

BindingContext BindingContext::fromFile(const std::string& /*file*/)
{
    throw std::logic_error{"Unimplemented"};
}

bool BindingContext::toFile(const std::string& /*file*/)
{
    throw std::logic_error{"Unimplemented"};
}

bool BindingContext::addKeyboardActionBinding(std::string action, KeyboardBindingData bindingData)
{
    auto [_, inserted] = _actionBindings.emplace(std::make_pair(std::move(bindingData), std::move(action)));
    return inserted;
}

bool BindingContext::addMouseActionBinding(std::string action, MouseButtonBindingData bindingData)
{
    const auto [_, inserted] = _mouseButtonBindings.emplace(std::make_pair(std::move(bindingData), std::move(action)));
    return inserted;
}

std::optional<std::string> BindingContext::mapKeyboardBindingToAction(const KeyboardBindingData& bindingData) const
{
    const auto I = _actionBindings.find(bindingData);
    if (I != std::end(_actionBindings)) {
        return I->second;
    } else {
        return {};
    }
}

std::optional<std::string> BindingContext::mapMouseButtonBindingToAction(
    const MouseButtonBindingData& bindingData) const
{
    const auto I = _mouseButtonBindings.find(bindingData);
    if (I != std::end(_mouseButtonBindings)) {
        return I->second;
    } else {
        return {};
    }
}

} // namespace frontier
