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

std::tuple<int, int, float> Renderer::projectTo2DAndSize(const Vec3& point, float size) const {
  int width = RendererConstants::INITIAL_WINDOW_WIDTH;
  int height = RendererConstants::INITIAL_WINDOW_HEIGHT;

  Vec4 transformedPoint = frustum.getViewProjectionMatrix() * Vec4(point, 1.0f);

  float perspectiveScale = 1.0f / transformedPoint.w;
  int projectedSize = size * perspectiveScale;

  // Normalized device coordinates
  float xNDC = transformedPoint.x / transformedPoint.w;
  float yNDC = transformedPoint.y / transformedPoint.w;

  // Convert NDC to screen coordinates where origin is the center of the screen
  int xScreen = static_cast<int>((xNDC * 0.5f + 0.5f) * width);
  int yScreen = static_cast<int>((-yNDC * 0.5f + 0.5f) * height);

  return {xScreen, yScreen, projectedSize};
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
  for (const auto& object : scene.getObjects())
  {
    Vec3 min = object->getMin();
    Vec3 max = object->getMax();

    if (frustum.isAABBInside(min, max))
    {
      LOG("Rendering object, inside frustum");
      object->render(*this, camera, options);
    }
  }

  // frustum.render(*this, options);
}

void Renderer::renderPoint(const Vec3& point, float size) const
{
  auto [x, y, projectSized] = projectTo2DAndSize(point, size);
  drawPoint(x, y, projectSized);
}

void Renderer::drawPoint(int x, int y, float size) const
{
  int intSize = static_cast<int>(size);
  SDL_Rect rect;
  rect.x = x - size / 2; // center before draw
  rect.y = y - size / 2; // center before draw
  rect.w = intSize;
  rect.h = intSize;
  SDL_RenderFillRect(renderer, &rect);
}

void Renderer::renderLine(const Vec3& start, const Vec3& end, float strokeWeight) const
{
  auto [x1, y1, startProjectedStokeWeight] = projectTo2DAndSize(start, strokeWeight);
  auto [x2, y2, endProjectedStrokeWeight] = projectTo2DAndSize(end, strokeWeight);
  drawLineBresenham(x1, y1, x2, y2, startProjectedStokeWeight, endProjectedStrokeWeight);
}

void Renderer::renderPolygon(const std::vector<Vec3>& vertices) const
{
  // TODO: address this, not sure exactly how yet
  const float defaultStrokeWeight = 1.0f;

  for (size_t i = 0; i < vertices.size(); ++i)
  {
    const Vec3& start = vertices[i];
    const Vec3& end = vertices[(i + 1) % vertices.size()];
    renderLine(start, end, defaultStrokeWeight);
  }
}

void Renderer::enableGrid(bool enable) { showGrid = enable; }

void Renderer::drawGrid()
{
	if (!showGrid) return;

  setColor(RendererConstants::GRID_COLOR);

  for (int x = 0; x < width; x += RendererConstants::SCALE)
  {
    SDL_RenderDrawLine(renderer, x, 0, x, height);
  }

  for (int y = 0; y < height; y += RendererConstants::SCALE)
  {
    SDL_RenderDrawLine(renderer, 0, y, width, y);
  }
}

void Renderer::drawLineBresenham(int x1, int y1, int x2, int y2, float startProjectedStokeWeight, float endProjectedFloatWeight) const {
  int dx = abs(x2 - x1);
  int dy = -abs(y2 - y1);
  int stepX = x1 < x2 ? 1 : -1;
  int stepY = y1 < y2 ? 1 : -1;
  int error = dx + dy;

  int length = std::max(dx, -dy);
  int step = 0;

  while (true)
  {
    float interpolationFactor = static_cast<float>(step) / static_cast<float>(length);
    float strokeWeight = MathUtility::lerp(startProjectedStokeWeight, endProjectedFloatWeight, interpolationFactor);
    drawPoint(x1, y1, strokeWeight);


    if (x1 == x2 && y1 == y2) break;

    int e2 = 2 * error;
    if (e2 >= dy)
    {
      if (x1 == x2) break;
      error += dy;
      x1 += stepX;
    }

    if (e2 <= dx)
    {
      if (y1 == y2) break;
      error += dx;
      y1 += stepY;
    }

    step++;
  }
}

// void Renderer::renderFrustum(const std::vector<Vec3>& corners) const {
//     // Draw near clip plane
//     renderLine(corners[0], corners[1]);
//     renderLine(corners[1], corners[3]);
//     renderLine(corners[3], corners[2]);
//     renderLine(corners[2], corners[0]);

//     // Draw far clip plane
//     setColor(RendererConstants::DEBUG_COLOR);
//     renderLine(corners[4], corners[5]);
//     renderLine(corners[5], corners[7]);
//     renderLine(corners[7], corners[6]);
//     renderLine(corners[6], corners[4]);

//     // Draw connecting lines between near and far planes
//     setColor(RendererConstants::FRUSTRUM_COLOR);
//     renderLine(corners[0], corners[4]);
//     renderLine(corners[1], corners[5]);
//     renderLine(corners[2], corners[6]);
//     renderLine(corners[3], corners[7]);
// }

// // TODO: remove?
// void Renderer::renderNormal(const Vec3& start, const Vec3& normal) const {
//     Vec3 end = start + normal * 20.0f; // Scale for visibility
//     renderLine(start, end);
// }

// void Renderer::renderStepByStep(const Scene& scene, ViewFrustum& frustum, Camera& camera, const RenderOptions& options) {
//     LOG("Rendering initial frame:");
//     frustum.update(camera);
//     clear();
//     renderScene(scene, frustum, camera, options);
//     present();

//     // Test moving forward
//     for (int step = 1; step <= 3; ++step) {
//         camera.moveForward(1.0f);
//         LOG_ARGS("Camera position after moving forward (step ", step, "):", camera.getPosition().x, camera.getPosition().y, camera.getPosition().z);
//         frustum.update(camera);
//         clear();
//         LOG_ARGS("Rendering frame after forward step ", step, ":");
//         renderScene(scene, frustum, camera, options);
//         present();
//     }

//     // Reset camera position
//     camera.position = Vec3(0.0f, 0.0f, 0.0f);

//     // Test moving forward
//     for (int step = 1; step <= 3; ++step) {
//         camera.moveBackward(1.0f);
//         LOG_ARGS("Camera position after moving backward (step ", step, "):", camera.getPosition().x, camera.getPosition().y, camera.getPosition().z);
//         frustum.update(camera);
//         clear();
//         LOG_ARGS("Rendering frame after backward step ", step, ":");
//         renderScene(scene, frustum, camera, options);
//         present();
//     }

//     // Reset camera position
//     camera.position = Vec3(0.0f, 0.0f, 0.0f);

//     // Test moving left
//     for (int step = 1; step <= 3; ++step) {
//         camera.moveLeft(1.0f);
//         LOG_ARGS("Camera position after moving left (step ", step, "):", camera.getPosition().x, camera.getPosition().y, camera.getPosition().z);
//         frustum.update(camera);
//         clear();
//         LOG_ARGS("Rendering frame after left step ", step, ":");
//         renderScene(scene, frustum, camera, options);
//         present();
//     }

//     // Reset camera position
//     camera.position = Vec3(0.0f, 0.0f, 0.0f);

//     // Test rotating right
//     for (int step = 1; step <= 3; ++step) {
//         camera.turnRight(0.1f);
//         LOG_ARGS("Camera direction after turning right (step ", step, "):", camera.getDirection().x, camera.getDirection().y, camera.getDirection().z);
//         frustum.update(camera);
//         clear();
//         LOG_ARGS("Rendering frame after turning right step ", step, ":");
//         renderScene(scene, frustum, camera, options);
//         present();
//     }

//     // Reset camera direction
//     camera.direction = Vec3(0.0f, 0.0f, -1.0f);
// }