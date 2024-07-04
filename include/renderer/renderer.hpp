#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <SDL2/SDL.h>
#include <vector>
#include "matrix4.hpp"

// Forward declarations of Point
struct Color;
class Point;
class Scene;
class Camera;
class RenderOptions;
class Vec3;
class ViewFrustum;


class Renderer {
  public:
    Renderer(const ViewFrustum& frustum);
    ~Renderer();

    int init();
    void clear();
    void present();

    void renderScene(const Scene& scene, const ViewFrustum& frustum, const Camera& camera, const RenderOptions& options);
    void renderPoint(const Vec3& point) const;
    void renderLine(const Vec3& start, const Vec3& end) const;
    void renderPolygon(const std::vector<Vec3>& vertices) const;
    void renderFrustum(const std::vector<Vec3>& corners) const;
    void renderNormal(const Vec3& start, const Vec3& normal) const;

    void renderStepByStep(const Scene& scene, ViewFrustum& frustum, Camera& camera, const RenderOptions& options);


    void setColor(const Color& color) const;
    std::pair<int, int> projectTo2D(const Vec3& point) const;

    // Debugging
    void enableGrid(bool enable);
    void drawGrid();
    bool isDebugViewEnabled() { return debugViewEnabled; }
    void toggleDebugView() { debugViewEnabled = !debugViewEnabled; }

    static float focalLength;

  private:
    void drawPoint(int x, int y) const;
    void drawVerticalLine(int x, int y1, int y2) const;
    void drawHorizontalLine(int x1, int x2, int y) const;
    void drawDiagonalLine(int x1, int y1, int x2, int y2) const;
    void drawLineBresenham(int x1, int y1, int x2, int y2) const;

    SDL_Window* window;
    SDL_Renderer* renderer;
    int width;
    int height;
    const ViewFrustum& frustum;
    // Debugging
    bool showGrid;
    bool debugViewEnabled;
};

#endif