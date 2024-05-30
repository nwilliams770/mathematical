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
  if (SDL_Init(SDL_INIT_VIDEO) != 0)
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

void Renderer::setColor(const SDL_Color& color) {
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
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

void Renderer::renderPoint(int x, int y)
{
  setColor(RendererConstants::DEBUG_COLOR);
  int scaledX = x * RendererConstants::SCALE;
  int scaledY = y * RendererConstants::SCALE;

  SDL_Rect rect;
  rect.x = scaledX;
  rect.y = scaledY;
  rect.w = RendererConstants::SCALE;
  rect.h = RendererConstants::SCALE;
  SDL_RenderFillRect(renderer, &rect);

}

void Renderer::renderLine(int x1, int y1, int x2, int y2)
{
  // detect horizontal, vertical, diagnoal
  drawLineBresenham(x1, y1, x2, y2);
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

void Renderer::renderPolygon(const std::vector<Point>& vertices) {};

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

void Renderer::drawVerticalLine(int x, int y1, int y2)
{
  if (y1 > y2) std::swap(y1, y2);
  for (int y = y1; y < y2; y++)
  {
    renderPoint(x, y);
  };
}

void Renderer::drawHorizontalLine(int x1, int x2, int y)
{
  if (x1 > x2) std::swap(x1, x2);
  for (int x = x1; x < x2; x++)
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
  int dx = abs(x2 - x1);
  int dy = abs(y2 - y1);
  float error = 0.5f;
  int x = x1;
  int y = y1;
  int stepX = dx > 0 ? 1 : -1;
  int stepY = dy > 0 ? 1 : -1;


  if (dx > dy)
  {

    float m = static_cast<float>(dx) / static_cast<float>(dy);
    while (x < x2)
    {
      renderPoint(x,y);
      x += stepX;
      error += m; // how much change in y for each one change in x
      if (error >= 0.5f) // 0.5 represents a half-pixel here?
      {
        y += stepY;
        error -= 1;
      }
    }
    renderPoint(x,y);
  } else {
    float m = static_cast<float>(dy) / static_cast<float>(dx);
    while (y < y2)
    {
      renderPoint(x,y);
      y += stepY;
      error += m; // how much change in y for each one change in x
      if (error >= 0.5f) // 0.5 represents a half-pixel here?
      {
        x += stepX;
        error -= 1;
      }
    }
  }
  renderPoint(x,y);
};




