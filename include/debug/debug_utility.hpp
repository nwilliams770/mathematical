#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <debug_options.hpp>
#include <vector>

namespace DebugUtility {
  std::vector<DebugOptions::DebugFlag> parseCommandLineArguments(int arc, char* argv[]);
}


#endif