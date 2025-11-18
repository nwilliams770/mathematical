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
#include "event_manager.hpp"
#include "view_frustum.hpp"
#include "point.hpp"

int main(int argc, char* argv[])
{
  Scene scene;
  std::string loadPath;
  RenderOptions options;
  ViewFrustum frustum(RendererConstants::FIELD_OF_VIEW_Y,
                        static_cast<float>(RendererConstants::INITIAL_WINDOW_WIDTH) / RendererConstants::INITIAL_WINDOW_HEIGHT,
                        RendererConstants::NEAR_CLIP,
                        RendererConstants::FAR_CLIP);
  Camera mainCamera(frustum);
  Camera debugCamera(frustum, Vec3(10.0f, 0.0f, 2.5f), Vec3(-1.0f, 0.0f, 0.0f));
  Renderer renderer (frustum);
  EventManager eventManager(mainCamera, debugCamera, renderer, options);

  Point testPoint = Point(0.0f, 0.0f, 10.0f, RendererConstants::DEBUG_COLOR, 100.0f);
  scene.addObject(&testPoint);

  std::vector<Options::Flag> flags = OptionsUtility::parseCommandLineArguments(argc, argv);
  for (const auto& flag : flags)
  {
    switch(flag)
    {
      case(Options::Flag::LoadFromPath):
        loadPath = OptionsUtility::getOptionValue(argc, argv, Options::LOAD_FROM_PATH);
      case(Options::Flag::RenderBoundingBoxes):
        options.renderBoundingBoxes = true;
        break;
      case(Options::Flag::RenderFrustrum):
        options.renderFrustum = true;
        break;
      default:
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

    const Camera& activeCamera = renderer.isDebugViewEnabled() ? debugCamera : mainCamera;

    frustum.update(activeCamera);

    renderer.renderScene(scene, frustum, activeCamera, options);
    renderer.present();
  }
    return 0;
}

