//src/bcppul.cpp
#include <iostream>
#include "bcppul/bcppul.h"
#include "bcppul/version_config.h"

namespace bcppul {
    void printHello() {
        std::cout << "Hello, BCPPUL" << std::endl;
        std::cout << "Bulka`s C++ Utils Library!" << std::endl;
        std::cout << "BCPPUL v" << BCPPUL_VERSION_STRING << std::endl;
        std::cout << "By Bulka: https://github.com/STimofii. Source code: https://github.com/STimofii/BCPPUL" << std::endl;
    }
} // namespace bcppul
