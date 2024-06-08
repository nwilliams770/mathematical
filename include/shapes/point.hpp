#ifndef POINT_HPP
#define POINT_HPP

#include "color.hpp"
#include "object.hpp" // because it inherits needs to know full definition
#include "json.hpp"

class Renderer; // Forward declaration of Renderer

class Point : public Object {
  public:
    Point(double x = 0, double y = 0, const Color& color = Color());
    ~Point() override = default; // Default destructor

    const double getX() const;
    const double getY() const;

    void setX(double newX);
    void setY(double newY);

    json toJSON() const override;
    void fromJSON(const json& j) override;

    void render(const Renderer& renderer) override;

  private:
    double x, y;
};

#endif