#pragma once

#include "ascent/drivers/actuators/pyro_channel.h"

/// @brief Motor igniter driver. Specialized pyro channel for motor ignition with additional safety constraints. \namespace ascent::drivers
namespace ascent::drivers
{
    /**
     * \class Igniter
     * @brief Motor igniter driver.
     *
     * Specialized pyro channel for motor ignition with
     * additional safety constraints.
     */
    class Igniter : public PyroChannel
    {
    public:
        using PyroChannel::PyroChannel;
        ~Igniter() override = default;
    };
} // namespace ascent::drivers