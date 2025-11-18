#include <algorithm>
#include <cmath>
#include "logging.hpp"
#include "renderer.hpp"
#include "renderer_constants.hpp"
#include "vec3.hpp"
#include "scene.hpp"
#include "view_frustum.hpp"
#include "camera.hpp"
#include "math_utility.hpp"
#include "plane.hpp"

float Renderer::focalLength = 100.0f;

Renderer::Renderer(const ViewFrustum& frustum)
  :
    frustum(frustum),
    window(nullptr), renderer(nullptr),
    width(RendererConstants::INITIAL_WINDOW_WIDTH),
    height(RendererConstants::INITIAL_WINDOW_WIDTH),
    showGrid(false) {}

Renderer::~Renderer()
{
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

int Renderer::init() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    LOG("SDL_Init Error: " + std::string(SDL_GetError()));
    return 1;
  }

  window = SDL_CreateWindow(
    "Mathematical",
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    width,
    height,
    SDL_WINDOW_RESIZABLE
  );
  if (window == nullptr)
  {
    LOG("SDL_CreateWindow Error: " + std::string(SDL_GetError()));
    SDL_Quit();
    return 1;
  }

  renderer = SDL_CreateRenderer(
    window,
    -1, // Selects the first rendering driver that supports the requested flags.
    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    // Uses hardware acceleration for rendering.
    // Synchronizes the renderer's present function with the screen's refresh
    // rate to avoid tearing.
  );
  if (renderer == nullptr)
  {
    SDL_DestroyWindow(window);
    LOG("SDL_CreateRenderer Error: " + std::string(SDL_GetError()));
    SDL_Quit();
    return 1;
  }

  return 0; // Zero indicates success
}

void Renderer::clear()
{
  setColor(RendererConstants::CLEAR_COLOR);
  SDL_RenderClear(renderer);
}

void Renderer::present()
{
  SDL_RenderPresent(renderer);
}

void Renderer::setColor(const Color& color) const {
  SDL_Color sdlColor = color.ToSDLColor();
  SDL_SetRenderDrawColor(renderer, sdlColor.r, sdlColor.g, sdlColor.b, sdlColor.a);
}

std::pair<int, int> Renderer::projectTo2D(const Vec3& point) const {
  int width = RendererConstants::INITIAL_WINDOW_WIDTH;
  int height = RendererConstants::INITIAL_WINDOW_HEIGHT;
  int winCenterX = width / 2;
  int winCenterY = height / 2;

  Vec4 transformedPoint = frustum.getViewProjectionMatrix() * Vec4(point, 1.0f);
  LOG_ARGS("Transformed Point:", transformedPoint.x, transformedPoint.y, transformedPoint.z, transformedPoint.w);

  // Check for precision issues
  if (fabs(transformedPoint.w) < 1e-6) {
    LOG_ARGS("Warning: Potential precision issue with w coordinate:", transformedPoint.w);
  }

  // Normalized device coordinates
  // NOTE: these seem more like screen space coordinates between -1 and 1
  float xNDC = transformedPoint.x / transformedPoint.w;
  float yNDC = transformedPoint.y / transformedPoint.w;
  LOG_ARGS("NDC:", xNDC, yNDC);

  // NOTE: NDCs are once they are in the range of 0 to 1.
  // (1 + xNDC) / 2;
  // (1 + yNDC) / 2;

  // Convert NDC to screen coordinates where origin is the center of the screen
  // int xScreen = static_cast<int>((xNDC * 0.5f + 0.5f) * width);
  // int yScreen = static_cast<int>((-yNDC * 0.5f + 0.5f) * height);
  // LOG_ARGS("Screen Coordinates:", xScreen, yScreen);

  // int xScreen = static_cast<int>((xNDC * width)/(2.0f * transformedPoint.w) + (width/2.0f));
  // int yScreen = static_cast<int>(-(yNDC * height)/(2.0f * transformedPoint.w) + (height/2.0f));

  int xScreen = static_cast<int>((xNDC * width / 2.0f) + winCenterX);
  int yScreen = static_cast<int>((-yNDC * height / 2.0f) + winCenterY);


  LOG_ARGS("NDC to screen conversion:", "NDC x", xNDC, "NDC y", yNDC, "Screen x", xScreen, "Screen y", yScreen);

  return {xScreen, yScreen};
}


// TODO: review
int Renderer::calculateOpacity(float distance, const ViewFrustum& frustum) {
  float nearClip = frustum.getNearClip();
  float farClip = frustum.getFarClip();
  float thresholdDistance = (farClip - nearClip) * 0.5f + nearClip;

  if (distance > farClip) return 0;
  if (distance < thresholdDistance) return 255;

  return static_cast<int>((1.0f - (distance - thresholdDistance) / (farClip - thresholdDistance)) * 255);
}


void Renderer::renderScene(const Scene& scene, const ViewFrustum& frustum, const Camera& camera, const RenderOptions& options)
{
  std::array<Plane, 6> frustumPlanes = frustum.getFrustumPlanes();
  for (const auto& object : scene.getObjects())
  {
    std::vector<Vec3> vertices = object->toPolygon();
    LOG("Vertices Pre clipping:");
    for (const auto& vertex : vertices)
    {
      LOG_ARGS("x", vertex.x, "y", vertex.y, "z", vertex.z);
    }
    for (const auto& plane : frustumPlanes)
    {
      vertices = MathUtility::sutherlandHodgmanClip(vertices, plane);
    }

    LOG("Vertices Post clipping:");
    for (const auto& vertex : vertices)
    {
      LOG_ARGS("x", vertex.x, "y", vertex.y, "z", vertex.z);
    }
    if (vertices.size() > 2)
    {
      Color renderColor = object->getRenderColor(camera);
      setColor(renderColor);
      LOG("Rendering polygon");
      renderPolygon(vertices);
    }
    else
    {
      LOG("Not rendering polygon");
    }

  }

  frustum.render(*this, options);
}


void Renderer::renderPolygon(const std::vector<Vec3>& vertices) const
{
  std::vector<std::pair<int, int>> projectedVertices;
  for (const auto& vertex : vertices)
  {
    auto [x, y] = projectTo2D(vertex);
    projectedVertices.emplace_back(x, y);
  }

    LOG("Vertices Post projection:");
    for (const auto& [x, y] : projectedVertices)
    {
      LOG_ARGS("x", x, "y", y);
    }

  // Draw the outline
  for (size_t i = 0; i < projectedVertices.size(); ++i) {
    const auto& [x1, y1] = projectedVertices[i];
    const auto& [x2, y2] = projectedVertices[(i + 1) % projectedVertices.size()];
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
  }

  fillPolygon(projectedVertices);
}

void Renderer::fillPolygon(const std::vector<std::pair<int, int>>& projectedVertices) const
{
  if (projectedVertices.size() < 3) return;

  int minY = std::numeric_limits<int>::max();
  int maxY = std::numeric_limits<int>::min();
  for (const auto& [x, y] : projectedVertices)
  {
    if (y < minY) minY = y;
    if (y > maxY) maxY = y;
  }

  for (int y = minY; y <= maxY; y++)
  {
    std::vector<int> intersections;

    for (size_t i = 0; i < projectedVertices.size(); i++)
    {
      const auto& [x1, y1] = projectedVertices[i];
      const auto& [x2, y2] = projectedVertices[(i + 1) % projectedVertices.size()];

      // Check if the edge (v1, v2) intersects with the scanline y
      if ((y1 <= y && y2 > y) || (y2 <= y && y1 > y)) {
        float interpolationFactor = (y - y1) / (y2 - y1);
        int x = static_cast<int>(MathUtility::lerp(x1, x2, interpolationFactor)); // X-coordinate of intersection
        intersections.push_back(x);
      }

      std::sort(intersections.begin(), intersections.end());

      // Fill between pairs of intersections
      for (size_t i = 0; i < intersections.size(); i += 2) {
        if (i + 1 < intersections.size()) {
          int x1 = intersections[i];
          int x2 = intersections[i + 1];
          SDL_RenderDrawLine(renderer, x1, y, x2, y);
        }
      }
    }
  }
}