#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <SDL2/SDL.h>
#include <vector>
#include "color.hpp"
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

    void renderPoint(int x, int y) const;
    void renderLine(int x1, int y1, int x2, int y2) const;
    void renderPolygon(const std::vector<Point>& vertices) const;
    void setColor(const Color& color) const;

    // Debugging
    void enableGrid(bool enable);
    void enableGridLabels(bool enable);

    void drawGrid();
    void handleEvents(bool& running);
  private:
    void drawVerticalLine(int x, int y1, int y2) const;
    void drawHorizontalLine(int x1, int x2, int y) const;
    void drawDiagonalLine(int x1, int y1, int x2, int y2) const;
    void drawLineBresenham(int x1, int y1, int x2, int y2) const;


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