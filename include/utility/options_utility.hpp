#ifndef OPTIONS_UTILITY_HPP
#define OPTIONS_UTILITY_HPP

#include <string>
#include <vector>
#include <cstring>
#include "logging.hpp"
#include "options.hpp"

// TODO: make this more robust, maybe throw errors when invalid args

namespace OptionsUtility {
  std::vector<Options::Flag> parseCommandLineArguments(int argc, char* argv[]);
  std::string getOptionValue(int argc, char* argv[], const std::string& option);
  std::string trim(const std::string& str);
}

inline std::vector<Options::Flag> OptionsUtility::parseCommandLineArguments(int argc, char* argv[]) {
  std::vector<Options::Flag> flags;
  for (int i = 1; i < argc; i++) {
    std::string arg = std::string(argv[i]);

    if (arg == Options::SHOW_GRID)
    {
      flags.push_back(Options::Flag::Grid);
    } else if (arg.find(Options::LOAD_FROM_PATH + "=") == 0)
    {
      flags.push_back(Options::Flag::LoadFromPath);
    } else if (arg == Options::RENDER_BOUNDING_BOXES)
    {
      flags.push_back(Options::Flag::RenderBoundingBoxes);
    }
  }
  return flags;
}


inline std::string OptionsUtility::getOptionValue(int argc, char* argv[], const std::string& option) {
  std::string prefix = option + "=";
  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    if (arg.find(prefix) == 0) {
      std::string value = arg.substr(prefix.size());
      return trim(value);
    }
  }
  return "";
}

inline std::string OptionsUtility::trim(const std::string& str) {
  size_t first = str.find_first_not_of(' ');
  if (first == std::string::npos) {
    return "";
  }
  size_t last = str.find_last_not_of(' ');
  return str.substr(first, last - first + 1);
}

#endif