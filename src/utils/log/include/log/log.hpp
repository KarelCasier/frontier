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
    Logger& operator<<(const T& value);

private:
    std::ostringstream _outBuffer;
};

#define LOGE Logger(LOG_ERROR)
#define LOGI Logger(LOG_INFO)
#define LOGD Logger(LOG_DEBUG)

} // namespace frontier

#include "../../src/log_impl.hpp"
