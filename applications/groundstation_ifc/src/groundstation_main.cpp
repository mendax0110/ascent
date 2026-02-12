#include "ascent/communication/radio_link.h"
#include "ascent/communication/command_parser.h"
#include <cstdio>

using namespace ascent::core;

/**
 * @brief Ground station interface logic.
 *
 * Handles telemetry reception and command transmission.
 */
class GroundStationMain
{
public:
    GroundStationMain() noexcept = default;
    ~GroundStationMain() = default;

    GroundStationMain(const GroundStationMain&) = delete;
    GroundStationMain& operator=(const GroundStationMain&) = delete;

    /**
     * @brief Initialize ground station interface.
     */
    StatusCode init() noexcept
    {
        return StatusCode::Ok;
    }

    /**
     * @brief Run the ground station communication loop.
     */
    void run() noexcept
    {
        // TODO: AdrGos Receive telemetry, send commands
    }
};
