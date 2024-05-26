#include <debug_options.hpp>
#include <debug_utility.hpp>
#include <string>
#include <vector>

std::vector<DebugOptions::DebugFlag> DebugUtility::parseCommandLineArguments(int argc, char* argv [])
{
  std::vector<DebugOptions::DebugFlag> flags;
  for (int i = 1; i < argc; i++)
  {
    std::string arg = std::string(argv[i]);
    if (arg == DebugOptions::SHOW_GRID)
    {
      flags.push_back(DebugOptions::DebugFlag::Grid);
    } else if (arg == DebugOptions::SHOW_GRID_LABELS)
    {
      flags.push_back(DebugOptions::DebugFlag::GridLabels);
    }
  }
  return flags;
}