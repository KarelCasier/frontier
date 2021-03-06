#pragma once

#include <sstream>

namespace frontier {

enum LogLevel {
    LOG_ERROR,
    LOG_WARN,
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
    inline Logger& operator<<(const T& value)
    {
        _outBuffer << value;
        return *this;
    }

private:
    std::stringstream _outBuffer;
};

#define LOGE Logger(LOG_ERROR)
#define LOGW Logger(LOG_WARN)
#define LOGI Logger(LOG_INFO)
#define LOGD Logger(LOG_DEBUG)

} // namespace frontier
