#include "event_manager.hpp"
#include "camera.hpp"
#include "logging.hpp"


EventManager::EventManager(Camera& mainCamera, Camera& debugCamera, Renderer& renderer)
  : mainCamera(mainCamera), debugCamera(debugCamera), renderer(renderer) {}

void EventManager::handleEvents(bool& running)
{
  SDL_Event event;
  while (SDL_PollEvent(&event))
  {
    if (event.type == SDL_QUIT)
    {
      running = false;
      return;
    } else if (event.type == SDL_KEYDOWN)
    {
      Camera& activeCamera = renderer.isDebugViewEnabled() ? debugCamera : mainCamera;
      handleKeyPress(event.key.keysym.sym, activeCamera);
    }
  }
}

// 'w', 'a', 's', 'd' for movement, 'q', 'e' for rotation, etc.
void EventManager::handleKeyPress(SDL_Keycode key, Camera& activeCamera) {
  float moveDistance = 1.0f; // Define movement step size
  float rotateAngle = 0.1f;  // Define rotation step size in radians

  LOG("Handling key press");
  switch (key) {
    case SDLK_t:
      renderer.toggleDebugView();
      break;
    case SDLK_w:
      activeCamera.moveForward(moveDistance);
      break;
    case SDLK_s:
      activeCamera.moveBackward(moveDistance);
      break;
    case SDLK_a:
      activeCamera.moveLeft(moveDistance);
      break;
    case SDLK_d:
      activeCamera.moveRight(moveDistance);
      break;
    case SDLK_q:
      activeCamera.turnLeft(rotateAngle);
      break;
    case SDLK_e:
      activeCamera.turnRight(rotateAngle);
      break;
    case SDLK_r:
      activeCamera.lookUp(rotateAngle);
      break;
    case SDLK_f:
      activeCamera.lookDown(rotateAngle);
      break;
    case SDLK_z:
      activeCamera.tiltLeft(rotateAngle);
      break;
    case SDLK_x:
      activeCamera.tiltRight(rotateAngle);
      break;
    default:
      break;
  }
}