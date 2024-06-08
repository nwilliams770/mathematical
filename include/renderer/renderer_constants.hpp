#ifndef RENDERER_CONSTANTS_HPP
#define RENDERER_CONSTANTS_HPP

#include "color.hpp"

namespace RendererConstants
{
  const char POINT_SYMBOL = '*';
  const char VERTEX_SYMBOL = '+';

  const int INITIAL_WINDOW_WIDTH = 600;
  const int INITIAL_WINDOW_HEIGHT = 600;
  const int SCALE = 20;

  const int ALPHA_OPAQUE = 255;

  const Color DEFAULT_OBJECT_COLOR = {255, 255, 255, ALPHA_OPAQUE};
  const Color GRID_COLOR = {200, 200, 200, ALPHA_OPAQUE};

  const Color DEBUG_COLOR = {227, 61, 148, ALPHA_OPAQUE};
  const Color CLEAR_COLOR = {0, 0, 0, ALPHA_OPAQUE};
}

#endif