#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "color.hpp"
#include "json.hpp"

class Renderer; // Forward declaration of Renderer
// only referencing so just needs to know about its existence

class Object {
  public:
    Object(const Color& color = Color()) : color(color) {};
    virtual ~Object() {};

    void setColor(const Color& newColor) { color = newColor; }
    Color getColor() const { return color; }

    virtual json toJSON() const = 0;
    virtual void fromJSON(const json& j) = 0;

    virtual void render(const Renderer& renderer) = 0;

  protected:
    Color color;
};

#endif