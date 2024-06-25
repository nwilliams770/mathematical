#ifndef EVENT_MANAGER_HPP
#define EVENT_MANAGER_HPP

#include <SDL2/SDL.h>
#include "camera.hpp"

class EventManager
{
  public:
    EventManager(Camera& camera);

    void handleEvents(bool& running);

  private:
    Camera& camera;

    void handleKeyPress(SDL_Keycode key);
};

#endif