#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <SDL2/SDL.h>
#include <vector>
#include "point.hpp"

class Point; // Forward declaration of Point
// only referencing so just needs to know about its existence

class Renderer {
  public:
    Renderer();
    ~Renderer();

    int init();
    void clear();
    void present();

    void renderPoint(int x, int y);
    void renderLine(int x1, int y1, int x2, int y2);
    void renderPolygon(const std::vector<Point>& vertices);

    // Debugging
    void enableGrid(bool enable);
    void enableGridLabels(bool enable);

    void drawGrid();
    void handleEvents(bool& running);
  private:
    void drawVerticalLine(int x, int y1, int y2);
    void drawHorizontalLine(int x1, int x2, int y);
    void drawDiagonalLine(int x1, int y1, int x2, int y2);
    void drawLineBresenham(int x1, int y1, int x2, int y2);

    void setColor(const SDL_Color& color);

    // Debugging
    bool showGrid;
    bool showGridLabels;

    SDL_Window* window;
    SDL_Renderer* renderer;
    int width;
    int height;

    void drawGridLabels();
};

#endif