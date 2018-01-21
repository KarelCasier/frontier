#pragma once

#include <sstream>

namespace frontier {

enum LogLevel {
    LOG_ERROR,
    LOG_INFO,
    LOG_DEBUG,
};

/// Logging class that outputs text to the console with levels corresponding to a color
///
/// Use: Logger(LOG_ERROR) << "Failure";
/// Also has simple defines:
/// LOGE << "Failure";
///
/// TODO: Support consoles without color output
class Logger {
public:
    Logger(LogLevel level);
    ~Logger();

    template <typename T>
    Logger& operator<<(const T& value)
    {
        _outBuffer << value;
        return *this;
    }

private:
    std::ostringstream _outBuffer;
};

} // namespace frontier
