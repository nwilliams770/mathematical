#include <vector>
#include "logging.hpp"
#include "renderer.hpp"
#include "options_utility.hpp"
#include "scene.hpp"
#include "save_data.hpp"
#include "scene_serializer.hpp"
#include "renderer_constants.hpp"
#include "render_options.hpp"

int main(int argc, char* argv[])
{
  Renderer renderer;
  Scene scene(renderer);
  std::string loadPath;
  RenderOptions options;

  std::vector<Options::Flag> flags = OptionsUtility::parseCommandLineArguments(argc, argv);
  for (const auto& flag : flags)
  {
    switch(flag)
    {
      // TODO: Make this better
      case(Options::Flag::Grid):
        LOG("enabling grid");
        renderer.enableGrid(true);
        break;
      case(Options::Flag::LoadFromPath):
        loadPath = OptionsUtility::getOptionValue(argc, argv, Options::LOAD_FROM_PATH);
        LOG("Load path extracted: " + loadPath);
      case(Options::Flag::RenderBoundingBoxes):
        LOG("render bounding boxes");
        options.renderBoundingBoxes = true;
        break;
    }
  }

  if (!loadPath.empty())
  {
    SaveData loadedData(scene);
    LOG("SaveData created at address: " + std::to_string(reinterpret_cast<uintptr_t>(&loadedData)));
    try
    {
      SceneSerializer::load(loadedData, loadPath);
      LOG_ARGS("Scene loaded with total objects", scene.getObjects().size());

    }
    catch (const std::exception& e)
    {
      LOG("Failed to load scene: " + std::string(e.what()));
      return -1;
    }
  }

  int initResult = renderer.init();
  LOG("Renderer initialized");
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
    scene.render(options);
    renderer.present();
  }
  LOG("Exiting main function");
}