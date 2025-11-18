#ifndef EVENT_MANAGER_HPP
#define EVENT_MANAGER_HPP

#include <SDL2/SDL.h>
#include "camera.hpp"
#include "renderer.hpp"
#include "render_options.hpp"

class EventManager
{
  public:
    EventManager(Camera& mainCamera, Camera& debugCamera, Renderer& renderer, RenderOptions& renderOptions);

    void handleEvents(bool& running);

  private:
    Camera& mainCamera;
    Camera& debugCamera;
    Renderer& renderer;
    RenderOptions& renderOptions;

    void handleKeyPress(SDL_Keycode key, Camera& activeCamera);
};

#endif