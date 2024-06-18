#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <SDL2/SDL.h>
#include <vector>

class Color;
class Point; // Forward declaration of Point
class Vec3;

class Renderer {
  public:
    Renderer();
    ~Renderer();

    int init();
    void clear();
    void present();

    void renderPoint(const Vec3& point) const;
    void renderLine(const Vec3& start, const Vec3& end) const;
    void renderPolygon(const std::vector<Vec3>& vertices) const;
    void setColor(const Color& color) const;
    static std::pair<int, int> projectTo2D(const Vec3& point);

    // Debugging
    void enableGrid(bool enable);
    void drawGrid();

    void handleEvents(bool& running);

    static float focalLength;

  private:
    void drawPoint(int x, int y) const;
    void drawVerticalLine(int x, int y1, int y2) const;
    void drawHorizontalLine(int x1, int x2, int y) const;
    void drawDiagonalLine(int x1, int y1, int x2, int y2) const;
    void drawLineBresenham(int x1, int y1, int x2, int y2) const;

    // Debugging
    bool showGrid;

    SDL_Window* window;
    SDL_Renderer* renderer;
    int width;
    int height;
};

#endif