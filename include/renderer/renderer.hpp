#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <ncurses.h>
#include <vector>
#include "point.hpp"

class Point; // Forward declaration of Point
// only referencing so just needs to know about its existence

class Renderer {
  public:
    Renderer();

    void init();
    void clear();
    void flush();

    void renderPoint(int x, int y);
    void renderLine(int x1, int y1, int x2, int y2);
    void renderPolygon(const std::vector<Point>& vertices);

    // Debugging
    void enableGrid(bool enable);
    void enableGridLabels(bool enable);

    void drawGrid();

  private:
    WINDOW* renderWin; // Window for rendering
    WINDOW* logWin;    // Window for logging
    int width, height;
    void drawVerticalLine(int x, int y1, int y2);
    void drawHorizontalLine(int x1, int x2, int y);
    void drawDiagonalLine(int x1, int y1, int x2, int y2);
    void drawLineBresenham(int x1, int y1, int x2, int y2);

    // Debugging
    bool showGrid;
    bool showGridLabels;

    void drawGridLabels();

};

#endif