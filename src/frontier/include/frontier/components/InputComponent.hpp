#pragma once

#include <functional>
#include <map>
#include <vector>

#include <input/BindingData.hpp>
#include <input/InputEvent.hpp>

namespace frontier {


class InputComponent {
public:
    using ActionCallback = std::function<void()>;
    using MouseCallback = std::function<void(int, int)>;

    InputComponent();

    void bindActionCallback(const std::string& action, ActionCallback callback);
    void bindMouseCallback(const std::string& action, MouseCallback callback);
    void bindMouseMotionCallback(const std::string& action, MouseCallback callback);

    void handleInputEvent(const ActionEvent& event);
    void handleInputEvent(const MouseEvent& event);
    void handleInputEvent(const MouseMotionEvent& event);

private:
    std::map<std::string, std::vector<ActionCallback>> actionCallbacks;
    std::map<std::string, std::vector<MouseCallback>> mouseButtonCallbacks;
    std::map<std::string, std::vector<MouseCallback>> mouseMotionCallbacks;
};

} // namespace frontier


