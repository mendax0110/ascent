#include "error_handler.h"
#include "ascent/core/logger.h"
#include <algorithm>
#include <array>

using namespace ascent::core;

std::array<ErrorRecord, ErrorHandler::kMaxErrors> ErrorHandler::s_errors = {};
uint32_t ErrorHandler::s_error_count = 0;
bool ErrorHandler::s_has_fatal = false;

void ErrorHandler::init() noexcept
{
    s_errors.fill(ErrorRecord{});
    s_error_count = 0;
    s_has_fatal = false;
}

void ErrorHandler::report(uint16_t source_id, StatusCode code, ErrorSeverity severity) noexcept
{
    if (s_error_count < kMaxErrors)
    {
        auto& record = s_errors[s_error_count];
        record.code = code;
        record.severity = severity;
        record.source_id = source_id;
        record.occurrence_count = 1;
        ++s_error_count;
    }

    if (severity == ErrorSeverity::Fatal)
    {
        s_has_fatal = true;
    }
}

bool ErrorHandler::hasFatal() noexcept
{
    return s_has_fatal;
}

uint32_t ErrorHandler::getErrorCount() noexcept
{
    return s_error_count;
}

void ErrorHandler::clearAll() noexcept
{
    s_errors.fill(ErrorRecord{});
    s_error_count = 0;
    s_has_fatal = false;
}

[[noreturn]] void ErrorHandler::panic(const char* msg) noexcept
{
    Logger::log(LogLevel::Fatal, "SYS", "PANIC: %s", msg);
    while (true)
    {
        // TODO: AdrGos Enter safe state, reset hardware...
    }
}
