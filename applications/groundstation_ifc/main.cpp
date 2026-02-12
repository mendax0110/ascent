#include "ascent/core/logger.h"

using namespace ascent::core;

int main()
{
    Logger::init(LogLevel::Info);
    Logger::log(LogLevel::Info, "GS", "ascent ground station interface");
    return 0;
}
