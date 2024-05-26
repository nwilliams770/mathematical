#ifndef DEBUG_OPTIONS_HPP
#define DEBUG_OPTIONS_HPP

#include <string>

namespace DebugOptions {
  const std::string SHOW_GRID = "--grid";
  const std::string SHOW_GRID_LABELS = "--grid-labels";

  enum class DebugFlag {
    None,
    Grid,
    GridLabels
  };
}


#endif