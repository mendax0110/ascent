#include <gtest/gtest.h>
#include "ascent/telemetry/telemetry_manager.h"
#include "ascent/telemetry/data_logger.h"
#include "ascent/telemetry/packet_formatter.h"
#include "ascent/communication/protocol_handler.h"

using namespace ascent;
using namespace ascent::core;

class TelemetryPipelineTest : public ::testing::Test
{
protected:
    telemetry::TelemetryManager mgr;
    telemetry::DataLogger logger;
    telemetry::PacketFormatter formatter;
    communication::ProtocolHandler protocol;

    void SetUp() override
    {
        mgr.init();
        logger.init();
        logger.setEnabled(true);
    }
};

TEST_F(TelemetryPipelineTest, FormatAndFrameStatus)
{
    uint8_t fmt_buf[256] = {};
    size_t written = 0;
    auto status = formatter.formatStatus(fmt_buf, sizeof(fmt_buf), written);
    EXPECT_EQ(status, StatusCode::Ok);

    uint8_t pkt_buf[512] = {};
    size_t pkt_size = 0;
    status = protocol.framePacket(fmt_buf, written, pkt_buf, pkt_size);
    EXPECT_EQ(status, StatusCode::Ok);
    EXPECT_GT(pkt_size, 0u);

    // Verify sync byte
    EXPECT_EQ(pkt_buf[0], communication::ProtocolHandler::kSyncByte);
}

TEST_F(TelemetryPipelineTest, FrameAndParse)
{
    uint8_t payload[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    uint8_t packet[512] = {};
    size_t pkt_size = 0;

    auto status = protocol.framePacket(payload, sizeof(payload), packet, pkt_size);
    EXPECT_EQ(status, StatusCode::Ok);

    uint8_t parsed[256] = {};
    size_t parsed_len = 0;
    status = protocol.parsePacket(packet, pkt_size, parsed, parsed_len);
    EXPECT_EQ(status, StatusCode::Ok);
    EXPECT_EQ(parsed_len, sizeof(payload));

    for (size_t i = 0; i < sizeof(payload); ++i)
    {
        EXPECT_EQ(parsed[i], payload[i]) << "Mismatch at byte " << i;
    }
}

TEST_F(TelemetryPipelineTest, LogFormattedPacket)
{
    uint8_t fmt_buf[256] = {};
    size_t written = 0;
    formatter.formatStatus(fmt_buf, sizeof(fmt_buf), written);

    auto status = logger.log(fmt_buf, written);
    EXPECT_EQ(status, StatusCode::Ok);
    EXPECT_EQ(logger.getBytesLogged(), static_cast<uint32_t>(written));
}

TEST_F(TelemetryPipelineTest, CrcDeterministic)
{
    uint8_t data[] = {0xDE, 0xAD, 0xBE, 0xEF};
    auto crc1 = communication::ProtocolHandler::computeCrc16(data, sizeof(data));
    auto crc2 = communication::ProtocolHandler::computeCrc16(data, sizeof(data));
    EXPECT_EQ(crc1, crc2);
}

TEST_F(TelemetryPipelineTest, CrcDiffersForDifferentData)
{
    uint8_t data1[] = {0x01, 0x02};
    uint8_t data2[] = {0x03, 0x04};
    auto crc1 = communication::ProtocolHandler::computeCrc16(data1, sizeof(data1));
    auto crc2 = communication::ProtocolHandler::computeCrc16(data2, sizeof(data2));
    EXPECT_NE(crc1, crc2);
}

TEST_F(TelemetryPipelineTest, EmptyPayloadFraming)
{
    uint8_t packet[64] = {};
    size_t pkt_size = 0;
    auto status = protocol.framePacket(nullptr, 0, packet, pkt_size);
    EXPECT_EQ(status, StatusCode::Ok);
    EXPECT_EQ(packet[0], communication::ProtocolHandler::kSyncByte);
}
