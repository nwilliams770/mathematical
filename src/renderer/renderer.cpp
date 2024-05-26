#include <algorithm>
#include <cmath>
#include <ncurses.h>
#include <vector>
#include <point.hpp>
#include "renderer.hpp"
#include "renderer_constants.hpp"
#ifndef NDEBUG
  #include "logging.hpp"
  #include "logging_constants.hpp"
#endif

Renderer::Renderer(): showGrid(false), showGridLabels(false) {};

void Renderer::init() {
  initscr();
  cbreak();
  noecho();
  start_color();
  init_pair(1, COLOR_RED, COLOR_BLACK); // Example color pair

  // Define the height of the log window
  #ifndef NDEBUG
    const int logHeight = LoggingConstants::MAX_LOG_LINES;
  #else
    const int logHeight = 0;
  #endif

  int renderHeight = LINES - logHeight;

  renderWin = newwin(renderHeight, COLS, 0, 0);
  getmaxyx(renderWin, height, width); // Get size of rendering window

  #ifndef NDEBUG
        // Create the log window and initialize the logger
        logWin = newwin(logHeight, COLS, renderHeight, 0);
        initLogger(logWin);
        wrefresh(logWin);
  #endif

  wrefresh(renderWin);
};

void Renderer::clear() {};
void Renderer::flush() {};

void Renderer::renderPoint(int x, int y) { mvaddch(y, x, RendererConstants::POINT_SYMBOL); }

void Renderer::renderLine(int x1, int y1, int x2, int y2)
{
  int dx = x1 - x2;
  int dy = y1 - y2;

}

void Renderer::renderPolygon(const std::vector<Point>& vertices) {};

void Renderer::enableGrid(bool enable) { showGrid = enable; }
void Renderer::enableGridLabels(bool enable) { showGridLabels = enable; }

void Renderer::drawGrid()
{
  if (!showGrid) return;

  // Draw Horizontals
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
        mvwaddch(renderWin, y, x, ACS_HLINE);
    }
  }

  // Draw Verticals
  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
        mvwaddch(renderWin, y, x, ACS_VLINE);
    }
  }

  wrefresh(renderWin);
}

void Renderer::drawVerticalLine(int x, int y1, int y2)
{
  if (y1 > y2) std::swap(y1, y2);
  for (int y = y1; y1 < y2; y++)
  {
    renderPoint(x, y);
  };
}

void Renderer::drawHorizontalLine(int x1, int x2, int y)
{
  if (x1 > x2) std::swap(x1, x2);
  for (int x = x1; x1 < x2; x++)
  {
    renderPoint(x, y);
  }
};

void Renderer::drawDiagonalLine(int x1, int y1, int x2, int y2)
{
  int dx = (x2 > x1) ? 1 : -1;
  int dy = (y2 > y1) ? 1 : -1;

  while (x1 != x2 && y1 != y2)
  {
    renderPoint(x1, y1);
    x1 += dx;
    y1 += dy;
  }
  renderPoint(x1, y1);
};

void Renderer::drawLineBresenham(int x1, int y1, int x2, int y2) {
  // int dx = abs(x2 - x1);
  // int dy = abs(y2 - y1);
  // float m = static_cast<float>(dx) / static_cast<float>(dy);
  // int x, y = x1, y1;
  // float error = 0.5f;

  // while (x < x2)
  // {
  //   renderPoint(x,y);
  //   x++;
  //   error += m; // how much change in y for each one change in x
  //   if (error >= 0.5f) // 0.5 represents a half-pixel here?
  //   {
  //     y++;
  //     error -= 1;
  //   }
  // }
  // renderPoint(x,y);
};




