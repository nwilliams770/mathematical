#include <algorithm>
#include <cmath>
#include "logging.hpp"
#include "renderer.hpp"
#include "renderer_constants.hpp"

Renderer::Renderer()
  :
    window(nullptr), renderer(nullptr),
    width(RendererConstants::INITIAL_WINDOW_WIDTH),
    height(RendererConstants::INITIAL_WINDOW_WIDTH),
    showGrid(false), showGridLabels(false) {};

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
};

void Renderer::clear()
{
  setColor(RendererConstants::CLEAR_COLOR);
  SDL_RenderClear(renderer);
};

void Renderer::present()
{
  SDL_RenderPresent(renderer);
};

void Renderer::setColor(const Color& color) const {
  SDL_Color sdlColor = color.ToSDLColor();
  SDL_SetRenderDrawColor(renderer, sdlColor.r, sdlColor.g, sdlColor.b, sdlColor.a);
}

void Renderer::handleEvents(bool& running)
{
  SDL_Event event;
  while (SDL_PollEvent(&event))
  {
    if (event.type == SDL_QUIT)
    {
      running = false;
      return;
    }
  }
}

void Renderer::renderPoint(const Vec3& point) const
{
  int scaledX = x * RendererConstants::SCALE;
  int scaledY = y * RendererConstants::SCALE;

  SDL_Rect rect;
  rect.x = scaledX;
  rect.y = scaledY;
  rect.w = RendererConstants::SCALE;
  rect.h = RendererConstants::SCALE;
  SDL_RenderFillRect(renderer, &rect);
}

void Renderer::renderLine(int x1, int y1, int x2, int y2) const
{
  if (x1 == x2)
  {
    drawVerticalLine(x1, y1, y2);
  }
  else if (y1 == y2)
  {
    drawHorizontalLine(x1, x2, y1);
  }
  else if (abs(x2 - x1) == abs(y2 - y1))
  {
    drawDiagonalLine(x1, y1, x2, y2);
  }
  else
  {
    drawLineBresenham(x1, y1, x2, y2);
  }
}

void Renderer::renderPolygon(const std::vector<Point>& vertices) const {};

void Renderer::enableGrid(bool enable) { showGrid = enable; }
void Renderer::enableGridLabels(bool enable) { showGridLabels = enable; }

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

void Renderer::drawVerticalLine(int x, int y1, int y2) const
{
  if (y1 > y2) std::swap(y1, y2);
  for (int y = y1; y < y2; y++)
  {
    renderPoint(x, y);
  };
}

void Renderer::drawHorizontalLine(int x1, int x2, int y) const
{
  if (x1 > x2) std::swap(x1, x2);
  for (int x = x1; x < x2; x++)
  {
    renderPoint(x, y);
  }
};

void Renderer::drawDiagonalLine(int x1, int y1, int x2, int y2) const
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

void Renderer::drawLineBresenham(int x1, int y1, int x2, int y2) const {
  int dx = abs(x2 - x1);
  int dy = -abs(y2 - y1);
  int stepX = x1 < x2 ? 1 : -1;
  int stepY = y1 < y2 ? 1 : -1;
  int error = dx + dy;

  while (true)
  {
    renderPoint(x1, y1);

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
  }
};




