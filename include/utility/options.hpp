#ifndef OPTIONS_HPP
#define OPTIONS_HPP

#include <string>

namespace Options {
  const std::string SHOW_GRID = "--grid";
  const std::string SHOW_GRID_LABELS = "--grid-labels";
  const std::string LOAD_FROM_PATH = "--loadfrompath";

  enum class Flag {
    None,
    Grid,
    GridLabels,
    LoadFromPath
  };
}


#endif