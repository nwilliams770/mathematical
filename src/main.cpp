#include <debug_utility.hpp>
#include <logging.hpp>
#include <renderer.hpp>
#include <vector>

int main(int argc, char* argv[])
{
  Renderer renderer;
  std::vector<DebugOptions::DebugFlag> debugFlags = DebugUtility::parseCommandLineArguments(argc, argv);
  for (const auto& flag : debugFlags)
  {
    switch(flag)
    {
      case(DebugOptions::DebugFlag::Grid):
        LOG("enabling grid");
        renderer.enableGrid(true);
        break;
      case(DebugOptions::DebugFlag::GridLabels):
        renderer.enableGridLabels(true);
        break;
    }
  }

  int initResult = renderer.init();
  if (initResult != 0)
  {
    LOG("Renderer failed to initialize");
    return initResult;
  }

  bool running = true;
  while (running)
  {
    renderer.handleEvents(running);
    renderer.clear();
    renderer.drawGrid();
    renderer.present();
  }
}