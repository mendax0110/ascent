#include "system.h"
#include "ascent/core/logger.h"

using namespace ascent::core;

int main()
{
    Logger::init(LogLevel::Debug);
    Logger::log(LogLevel::Info, "SIM", "ascent desktop simulation");

    System system;
    auto status = system.init();
    if (status != StatusCode::Ok)
    {
        Logger::log(LogLevel::Fatal, "SIM", "System init failed");
        return 1;
    }

    Logger::log(LogLevel::Info, "SIM", "System state: %u", static_cast<unsigned>(system.getState()));
    Logger::log(LogLevel::Info, "SIM", "Simulation complete");
    return 0;
}
