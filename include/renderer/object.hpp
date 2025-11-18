#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "color.hpp"
#include "json.hpp"
#include "render_options.hpp"
#include "vec3.hpp"
#include "camera.hpp"
#include "renderer.hpp"

class RenderOptions;

class Object {
  public:
    Object(const Color& color = Color()) : color(color) {};
    virtual ~Object() {};

    void setColor(const Color& color) { this->color = color; }
    Color getColor() const { return color; }
    Color getRenderColor(const Camera& camera) const
    {
      float distance = calculateDistance(camera);
      int distanceOpacity = Renderer::calculateOpacity(distance, camera.getFrustum());
      int renderOpacity = (color.getOpacity() * distanceOpacity) / 255; // TODO make const

      Color renderColor = color;
      renderColor.setOpacity(renderOpacity);

      return renderColor;
    }

    virtual json toJSON() const = 0;
    virtual void fromJSON(const json& j) = 0;

    virtual Vec3 getMin() const = 0;
    virtual Vec3 getMax() const = 0;

    virtual float calculateDistance(const Camera& camera) const = 0;

    virtual std::vector<Vec3> toPolygon() const = 0;

  protected:
    Color color;

    // Axis-aligned bounding box
    void renderBoundingBox(const Renderer& renderer, const RenderOptions& options) const;
};

#endif