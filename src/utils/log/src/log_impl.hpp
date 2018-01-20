#include <iostream>
#include <ostream>

namespace frontier {

namespace {

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

std::ostream& operator<<(std::ostream& os, const Code& code)
{
    return os << "\033[" << static_cast<int>(code) << "m";
}

std::ostream& operator<<(std::ostream& os, const LogLevel& level)
{
    switch (level) {
    case LOG_ERROR:
        return os << BG_RED << "E:" << BG_DEFAULT << " ";
    case LOG_INFO:
        return os << BG_YELLOW << "I:" << BG_DEFAULT << " ";
    case LOG_DEBUG:
        return os << BG_BLUE << "D:" << BG_DEFAULT << " ";
    default:
        return os << "U: ";
    }
}

} // namespace

Logger::Logger(LogLevel level)
{
    _outBuffer << level;
}

Logger::~Logger()
{
    std::cout << std::endl << _outBuffer.str();
}

template <typename T>
Logger& Logger::operator<<(const T& value)
{
    _outBuffer << value;
    return *this;
}

} // namespace frontier
