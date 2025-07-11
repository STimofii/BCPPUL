//examples/main.cpp
#include "bcppul/bcppul.h"
#include "bcppul/logging.h"
#include <iostream>

bcppul::Logger* logger1 = bcppul::getLogger("premain");

int main() {
    bcppul::printHello();
    bcppul::initLogging();
    bcppul::Logger* logger = bcppul::getLogger("main");
    *logger << bcppul::TRACE << "bulka!";

    return 0;
}
