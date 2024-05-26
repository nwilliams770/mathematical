#ifndef LOGGING_HPP
#define LOGGING_HPP

#include <string>

#ifndef NDEBUG

#include <ncurses.h>

void initLogger(WINDOW* window);
void logMessage(const std::string& msg);

#define LOG(msg) logMessage(msg)
#else
#define LOG(msg)
#endif

#endif