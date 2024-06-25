#include <vector>
#include "logging.hpp"
#include "renderer.hpp"
#include "options_utility.hpp"
#include "scene.hpp"
#include "save_data.hpp"
#include "scene_serializer.hpp"
#include "renderer_constants.hpp"
#include "render_options.hpp"
#include "camera.hpp"
#include "view_frustrum.hpp"
#include "event_manager.hpp"

int main(int argc, char* argv[])
{
  Renderer renderer;
  Scene scene;
  std::string loadPath;
  RenderOptions options;
  Camera camera;
  ViewFrustrum frustum(RendererConstants::FIELD_OF_VIEW_Y,
                        static_cast<float>(RendererConstants::INITIAL_WINDOW_WIDTH) / RendererConstants::INITIAL_WINDOW_HEIGHT,
                        RendererConstants::NEAR_CLIP,
                        RendererConstants::FAR_CLIP);

  EventManager eventManager(camera);

  std::vector<Options::Flag> flags = OptionsUtility::parseCommandLineArguments(argc, argv);
  for (const auto& flag : flags)
  {
    switch(flag)
    {
      // TODO: Make this grid better if not get rid of
      case(Options::Flag::Grid):
        renderer.enableGrid(true);
        break;
      case(Options::Flag::LoadFromPath):
        loadPath = OptionsUtility::getOptionValue(argc, argv, Options::LOAD_FROM_PATH);
      case(Options::Flag::RenderBoundingBoxes):
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
    eventManager.handleEvents(running);
    renderer.clear();

    frustum.update(camera);

    renderer.renderScene(scene, frustum, options);
    renderer.present();
  }
  LOG("Exiting main function");
}