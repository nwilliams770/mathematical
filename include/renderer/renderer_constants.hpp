#ifndef RENDERER_CONSTANTS_HPP
#define RENDERER_CONSTANTS_HPP

#include "color.hpp"

namespace RendererConstants
{
  // Window
  const int INITIAL_WINDOW_WIDTH = 600;
  const int INITIAL_WINDOW_HEIGHT = 600;

  // View Frustum
  const float FIELD_OF_VIEW_Y = 60.0f * (3.14159f / 180.0f); // 60 degrees to radians
  const float NEAR_CLIP = 0.1f;
  const float FAR_CLIP = 2000.0f;


  const int SCALE = 50;
  const float SCALE_FLOAT = 50.0f;

  // Colors
  const int ALPHA_OPAQUE = 255;
  const Color BOUNDING_BOX_COLOR = Color(255, 0, 0, ALPHA_OPAQUE);
  const Color DEFAULT_OBJECT_COLOR = {255, 255, 255, ALPHA_OPAQUE};
  const Color FRUSTRUM_COLOR = {200, 200, 200, ALPHA_OPAQUE};
  const Color GRID_COLOR = {200, 200, 200, ALPHA_OPAQUE};


  const Color DEBUG_COLOR = {227, 61, 148, ALPHA_OPAQUE};
  const Color CLEAR_COLOR = {0, 0, 0, ALPHA_OPAQUE};


}

#endif