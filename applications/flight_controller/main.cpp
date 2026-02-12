#include "system.h"
#include "ascent/core/logger.h"
#include "error_handler.h"
#include "scheduler.h"
#include "event_bus.h"

using namespace ascent::core;

int main()
{
    System system;
    auto status = system.init();
    if (status != StatusCode::Ok)
    {
        ErrorHandler::panic("System init failed");
    }

    system.run();

    return 0;
}
