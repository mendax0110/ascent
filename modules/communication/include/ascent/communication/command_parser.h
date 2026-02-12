#pragma once

#include "ascent/core/types.h"
#include <cstdint>
#include <cstddef>
#include <array>

/// @brief Command parser for ground station communication. Parses raw byte streams into structured Command objects. \namespace ascent::communication
namespace ascent::communication
{
    /// @brief Command type enumeration. \enum ascent::communication::CommandType
    enum class CommandType : uint8_t
    {
        None = 0,
        Arm,
        Disarm,
        Launch,
        Abort,
        SetConfig,
        RequestTelemetry,
        Ping
    };

    /// @brief Parsed command structure. \struct ascent::communication::Command
    struct Command
    {
        CommandType type = CommandType::None;
        uint32_t param = 0;
        uint16_t sequence_id = 0;
        bool valid = false;
    };

    /**
     * \class CommandParser
     * @brief Parses raw bytes into Command structures.
     */
    class CommandParser
    {
    public:
        CommandParser() noexcept;
        ~CommandParser() = default;

        CommandParser(const CommandParser&) = delete;
        CommandParser& operator=(const CommandParser&) = delete;
        CommandParser(CommandParser&&) = default;
        CommandParser& operator=(CommandParser&&) = default;

        /**
         * @brief Feed raw bytes into the parser.
         * @param data Raw data buffer.
         * @param length Number of bytes.
         */
        void feed(const uint8_t* data, size_t length) noexcept;

        /**
         * @brief Check if a complete command is available.
         * @return true if a complete command has been parsed and is ready to be retrieved.
         */
        bool hasCommand() const noexcept;

        /**
         * @brief Get the next parsed command.
         * @return Command structure containing the parsed command. Valid field indicates if the command is well-formed.
         */
        Command getCommand() noexcept;

    private:
        static constexpr size_t kBufferSize = 256;
        std::array<uint8_t, kBufferSize> m_buffer = {};
        size_t m_write_pos = 0;
        Command m_pending;
        bool m_has_pending = false;
    };
} // namespace ascent::communication