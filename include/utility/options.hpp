#ifndef OPTIONS_HPP
#define OPTIONS_HPP

#include <string>

namespace Options {
  const std::string SHOW_GRID = "--grid";
  const std::string LOAD_FROM_PATH = "--loadfrompath";
  const std::string RENDER_BOUNDING_BOXES = "--renderboundingboxes";
  const std::string RENDER_FRUSTRUM = "--renderfrustrum";

  enum class Flag {
    None,
    Grid,
    LoadFromPath,
    RenderBoundingBoxes,
    RenderFrustrum,
  };
}


#endif