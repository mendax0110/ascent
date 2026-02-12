#pragma once

#include <cstdint>
#include <cstddef>
#include <cstdarg>
#include <array>
#include "ascent/core/config.h"

/// @brief Core logging system. \namespace ascent::core
namespace ascent::core
{
    /// @brief Log severity levels. \enum LogLevel
    enum class LogLevel : uint8_t
    {
        Trace = 0,
        Debug,
        Info,
        Warning,
        Error,
        Fatal
    };

    /**
     * \class Logger
     * @brief Static logger with minimal overhead.
     *
     * Uses a fixed-size ring buffer internally. No heap allocation.
     */
    class Logger
    {
    public:
        Logger() = delete;
        ~Logger() = delete;

        /**
         * @brief Initialize the logger subsystem.
         * @param min_level Minimum severity level to output.
         */
        static void init(LogLevel min_level = LogLevel::Info) noexcept;

        /**
         * @brief Log a formatted message.
         * @param level Severity level.
         * @param tag Component tag.
         * @param fmt printf-style format string.
         */
        static void log(LogLevel level, const char* tag, const char* fmt, ...) noexcept;

        /**
         * @brief Set the minimum log level at runtime.
         */
        static void setLevel(LogLevel level) noexcept;

        /**
         * @brief Get the current minimum log level.
         */
        static LogLevel getLevel() noexcept;

    private:
        static LogLevel s_min_level;
        static std::array<char, Config::kLogBufferSize> s_buffer;
    };
} // namespace ascent::core
