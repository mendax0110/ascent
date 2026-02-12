#include <gtest/gtest.h>
#include "error_handler.h"

using namespace ascent::core;

class ErrorHandlerTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        ErrorHandler::init();
    }
};

TEST_F(ErrorHandlerTest, InitClearsState)
{
    EXPECT_EQ(ErrorHandler::getErrorCount(), 0u);
    EXPECT_FALSE(ErrorHandler::hasFatal());
}

TEST_F(ErrorHandlerTest, ReportIncreasesCount)
{
    ErrorHandler::report(1, StatusCode::Error, ErrorSeverity::Warning);
    EXPECT_EQ(ErrorHandler::getErrorCount(), 1u);
}

TEST_F(ErrorHandlerTest, ReportMultiple)
{
    ErrorHandler::report(1, StatusCode::Error, ErrorSeverity::Warning);
    ErrorHandler::report(2, StatusCode::Timeout, ErrorSeverity::Recoverable);
    ErrorHandler::report(3, StatusCode::Busy, ErrorSeverity::Critical);
    EXPECT_EQ(ErrorHandler::getErrorCount(), 3u);
}

TEST_F(ErrorHandlerTest, FatalSetsFlag)
{
    EXPECT_FALSE(ErrorHandler::hasFatal());
    ErrorHandler::report(1, StatusCode::HardwareFault, ErrorSeverity::Fatal);
    EXPECT_TRUE(ErrorHandler::hasFatal());
}

TEST_F(ErrorHandlerTest, WarningDoesNotSetFatal)
{
    ErrorHandler::report(1, StatusCode::Error, ErrorSeverity::Warning);
    EXPECT_FALSE(ErrorHandler::hasFatal());
}

TEST_F(ErrorHandlerTest, ClearAllResetsEverything)
{
    ErrorHandler::report(1, StatusCode::Error, ErrorSeverity::Fatal);
    EXPECT_TRUE(ErrorHandler::hasFatal());
    EXPECT_EQ(ErrorHandler::getErrorCount(), 1u);

    ErrorHandler::clearAll();
    EXPECT_EQ(ErrorHandler::getErrorCount(), 0u);
    EXPECT_FALSE(ErrorHandler::hasFatal());
}

TEST_F(ErrorHandlerTest, DoesNotOverflowBuffer)
{
    for (size_t i = 0; i < ErrorHandler::kMaxErrors + 10; ++i)
    {
        ErrorHandler::report(static_cast<uint16_t>(i), StatusCode::Error, ErrorSeverity::Warning);
    }
    EXPECT_EQ(ErrorHandler::getErrorCount(), static_cast<uint32_t>(ErrorHandler::kMaxErrors));
}
