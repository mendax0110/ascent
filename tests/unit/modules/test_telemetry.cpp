#include <gtest/gtest.h>
#include "ascent/telemetry/telemetry_manager.h"
#include "ascent/telemetry/data_logger.h"
#include "ascent/telemetry/packet_formatter.h"

using namespace ascent::telemetry;
using namespace ascent::core;

class TelemetryManagerTest : public ::testing::Test
{
protected:
    TelemetryManager mgr;
};

TEST_F(TelemetryManagerTest, InitSucceeds)
{
    auto status = mgr.init();
    EXPECT_EQ(status, StatusCode::Ok);
}

TEST_F(TelemetryManagerTest, InitialPacketCount)
{
    EXPECT_EQ(mgr.getPacketsSent(), 0u);
}

TEST_F(TelemetryManagerTest, SetRate)
{
    mgr.setRate(50);
}

TEST_F(TelemetryManagerTest, UpdateDoesNotCrash)
{
    mgr.init();
    mgr.update();
}

class DataLoggerTest : public ::testing::Test
{
protected:
    DataLogger logger;

    void SetUp() override
    {
        logger.init();
        logger.setEnabled(true);
    }
};

TEST_F(DataLoggerTest, InitSucceeds)
{
    DataLogger l;
    const auto status = l.init();
    EXPECT_EQ(status, StatusCode::Ok);
}

TEST_F(DataLoggerTest, InitialBytesZero)
{
    DataLogger l;
    l.init();
    EXPECT_EQ(l.getBytesLogged(), 0u);
}

TEST_F(DataLoggerTest, LogData)
{
    constexpr uint8_t data[] = {0x01, 0x02, 0x03, 0x04};
    const auto status = logger.log(data, sizeof(data));
    EXPECT_EQ(status, StatusCode::Ok);
    EXPECT_EQ(logger.getBytesLogged(), 4u);
}

TEST_F(DataLoggerTest, LogMultiple)
{
    constexpr uint8_t data[8] = {};
    logger.log(data, 8);
    logger.log(data, 8);
    EXPECT_EQ(logger.getBytesLogged(), 16u);
}

TEST_F(DataLoggerTest, DisabledLoggerRejects)
{
    logger.setEnabled(false);
    constexpr uint8_t data[] = {0x01};
    const auto status = logger.log(data, 1);
    EXPECT_NE(status, StatusCode::Ok);
}

TEST_F(DataLoggerTest, FlushDoesNotCrash)
{
    constexpr uint8_t data[16] = {};
    logger.log(data, sizeof(data));
    logger.flush();
}

TEST(PacketFormatter, FormatStatusDoesNotCrash)
{
    PacketFormatter fmt;
    uint8_t buffer[256] = {};
    size_t written = 0;
    const auto status = fmt.formatStatus(buffer, sizeof(buffer), written);
    EXPECT_EQ(status, StatusCode::Ok);
}

TEST(PacketFormatter, FormatNavigationDoesNotCrash)
{
    PacketFormatter fmt;
    uint8_t buffer[256] = {};
    size_t written = 0;
    const auto status = fmt.formatNavigation(buffer, sizeof(buffer), written);
    EXPECT_EQ(status, StatusCode::Ok);
}
