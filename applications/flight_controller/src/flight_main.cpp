#include "system.h"
#include "ascent/core/logger.h"
#include "scheduler.h"
#include "event_bus.h"
#include "error_handler.h"

using namespace ascent::core;

/**
 * @brief Main flight application logic.
 *
 * Initializes all subsystems, registers scheduler tasks,
 * and runs the main control loop.
 */
class FlightMain
{
public:
    FlightMain() noexcept = default;
    ~FlightMain() = default;

    FlightMain(const FlightMain&) = delete;
    FlightMain& operator=(const FlightMain&) = delete;

    /**
     * @brief Initialize all flight subsystems.
     */
    StatusCode init() noexcept
    {
        const auto status = m_system.init();
        if (status != StatusCode::Ok)
        {
            return status;
        }

        return StatusCode::Ok;
    }

    /**
     * @brief Run the flight control loop.
     */
    void run() noexcept
    {
        m_system.run();
    }

private:
    System m_system;
    Scheduler m_scheduler;
};
