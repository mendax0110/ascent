#include "ascent/core/logger.h"
#include <cstdio>
#include <algorithm>
#include <array>

using namespace ascent::core;

LogLevel Logger::s_min_level = LogLevel::Info;
std::array<char, Config::kLogBufferSize> Logger::s_buffer = {};

void Logger::init(const LogLevel min_level) noexcept
{
    s_min_level = min_level;
    s_buffer.fill('\0');
}

void Logger::log(LogLevel level, const char* tag, const char* fmt, ...) noexcept
{
    if (level < s_min_level)
    {
        return;
    }

    static constexpr std::array<const char*, 6> kLevelNames =
    {
        "TRC", "DBG", "INF", "WRN", "ERR", "FTL"
    };

    const auto lvl_idx = static_cast<uint8_t>(level);
    const int prefix_len = std::snprintf(
        s_buffer.data(), s_buffer.size(), "[%s][%s] ", kLevelNames[lvl_idx], tag);

    if (prefix_len > 0 && static_cast<size_t>(prefix_len) < s_buffer.size())
    {
        va_list args;
        va_start(args, fmt);
        std::vsnprintf(s_buffer.data() + prefix_len, s_buffer.size() - static_cast<size_t>(prefix_len), fmt, args);
        va_end(args);
    }
}

void Logger::setLevel(const LogLevel level) noexcept
{
    s_min_level = level;
}

LogLevel Logger::getLevel() noexcept
{
    return s_min_level;
}
