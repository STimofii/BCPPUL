#pragma once
#ifndef BCPPUL_H
#define BCPPUL_H

#include <iostream>


#ifdef _WIN32
#ifdef BCPPUL_EXPORTS
#define BCPPUL_API __declspec(dllexport)
#else
#define BCPPUL_API __declspec(dllimport)
#endif
#else 
#define BCPPUL_API
#endif

namespace bcppul {
    BCPPUL_API void printHello();
} // namespace bcppul

#endif // BCPPUL_H