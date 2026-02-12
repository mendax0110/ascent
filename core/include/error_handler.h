#pragma once

#include <cstdint>
#include <cstddef>
#include <array>
#include "ascent/core/types.h"

/// @brief Centralized error handling system. \namespace ascent::core
namespace ascent::core
{
    /// @brief Error severity levels. \enum ErrorSeverity
    enum class ErrorSeverity : uint8_t
    {
        Warning,
        Recoverable,
        Critical,
        Fatal
    };

    /// @brief Error record structure for logging and diagnostics. \struct ErrorRecord
    struct ErrorRecord
    {
        StatusCode code = StatusCode::Ok;
        ErrorSeverity severity = ErrorSeverity::Warning;
        uint32_t timestamp_ms = 0;
        uint16_t source_id = 0;
        uint16_t occurrence_count = 0;
    };

    /**
     * \class ErrorHandler
     * @brief Centralized error handler with fault counters.
     *
     * Provides static methods for reporting and querying system errors.
     * Non-allocating, uses a fixed-size error log.
     */
    class ErrorHandler
    {
    public:
        static constexpr size_t kMaxErrors = 32;

        ErrorHandler() = delete;
        ~ErrorHandler() = delete;

        /**
         * @brief Initialize the error handler subsystem.
         */
        static void init() noexcept;

        /**
         * @brief Report an error.
         * @param source_id Identifier of the reporting subsystem.
         * @param code Status code describing the error.
         * @param severity Error severity.
         */
        static void report(uint16_t source_id, StatusCode code, ErrorSeverity severity) noexcept;

        /**
         * @brief Check if any fatal error is active.
         * @return True if a fatal error has been reported, false otherwise.
         */
        static bool hasFatal() noexcept;

        /**
         * @brief Get total error count.
         * @return Total number of errors reported.
         */
        static uint32_t getErrorCount() noexcept;

        /**
         * @brief Clear all error records.
         */
        static void clearAll() noexcept;

        /**
         * @brief Fatal handler - enters safe state. Does not return.
         * @param msg Optional message describing the fatal error.
         */
        [[noreturn]] static void panic(const char* msg) noexcept;

    private:
        static std::array<ErrorRecord, kMaxErrors> s_errors;
        static uint32_t s_error_count;
        static bool s_has_fatal;
    };
} // namespace ascent::core
