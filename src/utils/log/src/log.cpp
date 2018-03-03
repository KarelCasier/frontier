#include <log/log.hpp>

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <ostream>

namespace {

using namespace std::chrono;

/// Modifer codes to alter output color to the console
/// Modified from https://stackoverflow.com/questions/2616906/how-do-i-output-coloured-text-to-a-linux-terminal
enum Code {
    FG_RED = 31,
    FG_GREEN = 32,
    FG_YELLOW = 33,
    FG_BLUE = 34,
    FG_DEFAULT = 39,
    BG_RED = 41,
    BG_GREEN = 42,
    BG_YELLOW = 43,
    BG_BLUE = 44,
    BG_DEFAULT = 49
};

inline std::ostream& operator<<(std::ostream& os, const Code& code)
{
    return os << "\033[" << static_cast<int>(code) << "m";
}

inline std::ostream& operator<<(std::ostream& os, const frontier::LogLevel& level)
{
    switch (level) {
    case frontier::LOG_ERROR:
        return os << BG_RED << "  E  " << BG_DEFAULT << " ";
    case frontier::LOG_WARN:
        return os << BG_YELLOW << "  W  " << BG_DEFAULT << " ";
    case frontier::LOG_INFO:
        return os << BG_GREEN << "  I  " << BG_DEFAULT << " ";
    case frontier::LOG_DEBUG:
        return os << BG_BLUE << "  D  " << BG_DEFAULT << " ";
    default:
        return os << "  U  " << " ";
    }
}

} // namespace

namespace frontier {

Logger::Logger(LogLevel level)
{
    auto now_time_t = system_clock::to_time_t(system_clock::now());
    auto now_tm = *std::localtime(&now_time_t);
    _outBuffer << std::put_time(&now_tm, "%H:%M:%S") << " ";
    _outBuffer << level;
}

Logger::~Logger()
{
    std::cout << _outBuffer.str() << std::endl;
    _outBuffer.flush();
}

} // namespace frontier
