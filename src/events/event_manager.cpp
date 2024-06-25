#include "event_manager.hpp"
#include "camera.hpp"
#include "logging.hpp"


EventManager::EventManager(Camera& camera) : camera(camera) {}

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
      handleKeyPress(event.key.keysym.sym);
    }
  }
}

// 'w', 'a', 's', 'd' for movement, 'q', 'e' for rotation, etc.
void EventManager::handleKeyPress(SDL_Keycode key) {
  float moveDistance = 1.0f; // Define movement step size
  float rotateAngle = 0.1f;  // Define rotation step size in radians

  LOG("Handling key press");
  switch (key) {
    case SDLK_w:
        camera.moveForward(moveDistance);
        break;
    case SDLK_s:
        camera.moveBackward(moveDistance);
        break;
    case SDLK_a:
        camera.moveLeft(moveDistance);
        break;
    case SDLK_d:
        camera.moveRight(moveDistance);
        break;
    case SDLK_q:
        camera.turnLeft(rotateAngle);
        break;
    case SDLK_e:
        camera.turnRight(rotateAngle);
        break;
    case SDLK_r:
        camera.lookUp(rotateAngle);
        break;
    case SDLK_f:
        camera.lookDown(rotateAngle);
        break;
    case SDLK_z:
        camera.tiltLeft(rotateAngle);
        break;
    case SDLK_x:
        camera.tiltRight(rotateAngle);
        break;
    default:
        break;
  }
}