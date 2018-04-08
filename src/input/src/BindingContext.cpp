#include <input/BindingContext.hpp>

namespace {

template <typename ValT, typename KeyT>
std::optional<ValT> findKey(const std::unordered_map<KeyT, ValT>& map, const KeyT& key)
{
    const auto I = map.find(key);
    if (I != std::end(map)) {
        return I->second;
    } else {
        return {};
    }
}

} // namespace

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

bool BindingContext::addMouseMotionBinding(std::string action, MouseMotionBindingData bindingData)
{
    const auto [_, inserted] = _mouseMotionBindings.emplace(std::make_pair(std::move(bindingData), std::move(action)));
    return inserted;
}

std::optional<std::string> BindingContext::mapKeyboardBindingToAction(const KeyboardBindingData& bindingData) const
{
    return findKey(_actionBindings, bindingData);
}

std::optional<std::string> BindingContext::mapMouseButtonBindingToAction(
    const MouseButtonBindingData& bindingData) const
{
    return findKey(_mouseButtonBindings, bindingData);
}

std::optional<std::string> BindingContext::mapMouseMotionBindingToAction(
    const MouseMotionBindingData& bindingData) const
{
    return findKey(_mouseMotionBindings, bindingData);
}

} // namespace frontier
