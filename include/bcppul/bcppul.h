//include/bcppul/bcppul.h
#pragma once
#ifndef BCPPUL_H
#define BCPPUL_H

#include <iostream>


#ifdef _WIN32
  #ifdef BCPPUL_EXPORTS
    #define BCPPUL_API __declspec(dllexport)
  #elif defined(BCPPUL_SHARED_USE)
    #define BCPPUL_API __declspec(dllimport)
  #else
    #define BCPPUL_API
  #endif
#else
  #define BCPPUL_API
#endif

//#define BCPPUL_VERION_MAJOR 0
//#define BCPPUL_VERION_MINOR 1
//#define BCPPUL_VERION_PATCH 0

namespace bcppul {
    BCPPUL_API void printHello();
} // namespace bcppul

#endif // BCPPUL_H