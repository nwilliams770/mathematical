#ifndef COLOR_HPP
#define COLOR_HPP

#include <SDL2/SDL.h>
#include "json.hpp"

struct Color {
  int r, g, b, a;

  Color(int red = 255, int green = 255, int blue = 255, int alpha = 255)
    : r(red), g(green), b(blue), a(alpha) {}

  SDL_Color ToSDLColor() const
  {
    SDL_Color sdlColor = { static_cast<Uint8>(r), static_cast<Uint8>(g), static_cast<Uint8>(b), static_cast<Uint8>(a) };
    return sdlColor;
  }

  json toJSON() const
  {
    return json{
      {JsonKeys::COLOR_RED, r},
      {JsonKeys::COLOR_GREEN, g},
      {JsonKeys::COLOR_BLUE, b},
      {JsonKeys::COLOR_ALPHA, a}
    };
  }

  static Color fromJSON(const json& j)
  {
    return Color(
      j.at(JsonKeys::COLOR_RED).get<int>(),
      j.at(JsonKeys::COLOR_GREEN).get<int>(),
      j.at(JsonKeys::COLOR_BLUE).get<int>(),
      j.at(JsonKeys::COLOR_ALPHA).get<int>()
    );
  }


};

#endif