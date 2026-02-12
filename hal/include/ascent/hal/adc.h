#pragma once

#include "ascent/hal/types.h"

/// @brief ADC channel abstraction. \namespace ascent::hal
namespace ascent::hal
{
    /**
     * \class Adc
     * @brief ADC channel abstraction.
     */
    class Adc
    {
    public:
        /**
         * @brief Construct and initialize ADC channel.
         * @param channel ADC channel identifier.
         * @param resolution_bits ADC resolution (8, 10, 12, 16).
         */
        explicit Adc(AdcChannel channel, uint8_t resolution_bits = 12) noexcept;
        ~Adc() noexcept;

        Adc(const Adc&) = delete;
        Adc& operator=(const Adc&) = delete;
        Adc(Adc&& other) noexcept;
        Adc& operator=(Adc&& other) noexcept;

        /**
         * @brief Read raw ADC value.
         * @return Result containing raw value.
         */
        core::Result<uint16_t> readRaw() noexcept;

        /**
         * @brief Read voltage in millivolts.
         * @param vref_mv Reference voltage in millivolts.
         * @return Result containing voltage in millivolts.
         */
        core::Result<uint32_t> readMillivolts(uint32_t vref_mv = 3300) noexcept;

    private:
        AdcChannel m_channel;
        uint8_t m_resolution_bits;
        bool m_initialized = false;
    };
} // namespace ascent::hal