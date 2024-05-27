#ifndef LOGGING_HPP
#define LOGGING_HPP

#include <string>
#include <iostream>

void logMessage(const std::string& msg);

#ifdef NDEBUG
    #define LOG(msg) // No-op in release mode
#else
    #define LOG(msg) logMessage(msg)
#endif

#endif