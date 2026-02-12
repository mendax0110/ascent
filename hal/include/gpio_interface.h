#pragma once

#include <cstdint>
#include "ascent/core/types.h"

/// @brief GPIO pin abstraction with RAII lifecycle. \namespace ascent::hal
namespace ascent::hal
{
    /**
     * \class IGpio
     * @brief Abstract GPIO interface.
     *
     * Allows mocking GPIO for desktop simulation.
     */
    class IGpio
    {
    public:
        virtual ~IGpio() = default;

        /**
         * @brief Set the GPIO pin to high.
         * 
         */
        virtual void setHigh() noexcept = 0;
        
        /**
         * @brief Set the GPIO pin to low.
         * 
         */
        virtual void setLow() noexcept = 0;
        
        /**
         * @brief Toggle the GPIO pin state.
         * 
         */
        virtual void toggle() noexcept = 0;
        
        /**
         * @brief Read the current state of the GPIO pin.
         * @return true if the pin is high, false if low.
         */
        virtual bool read() const noexcept = 0;

    protected:
        IGpio() = default;
        IGpio(const IGpio&) = default;
        IGpio& operator=(const IGpio&) = default;
        IGpio(IGpio&&) = default;
        IGpio& operator=(IGpio&&) = default;
    };
} // namespace ascent::hal