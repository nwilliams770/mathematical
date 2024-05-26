#ifndef NDEBUG

#include <logging.hpp>
#include <iostream>

static WINDOW* logWindow = nullptr;
static int logLineCount = 0;

void initLogger(WINDOW* window)
{
  if (window)
  {
    logWindow = window;
    scrollok(logWindow, TRUE);
  }
}

void logMessage(const std::string& msg)
{
  if (logWindow)
  {
    int maxY, maxX;
    getmaxyx(logWindow, maxY, maxX);

    if (logLineCount >= maxY)
    {
      wscrl(logWindow, 1);
      logLineCount = maxY - 1;
    }

    mvwprintw(logWindow, logLineCount++, 0, "[LOG] %s", msg.c_str());
    wrefresh(logWindow);
  } else {
    std::cout << "[LOG]" << msg << std::endl;
  }
}

#endif