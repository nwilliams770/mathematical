#ifndef POINT_HPP
#define POINT_HPP

#include "object.hpp" // because it inherits needs to know full definition

class Renderer; // Forward declaration of Renderer

class Point : public Object {
  public:
    Point(double x, double y);
    ~Point() override = default; // Default destructor

    const double getX() const;
    const double getY() const;

    void setX(double newX);
    void setY(double newY);

    void render(const Renderer& renderer) override;

  private:
    double x, y;
};

#endif