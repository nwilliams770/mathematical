#ifndef POINT_HPP
#define POINT_HPP

#include "object.hpp"

class Point : public Object {
  public:
    Point(double x, double y);

    const double getX() const;
    const double getY() const;

    void setX(double newX);
    void setY(double newY);

    void render() override;

  private:
    double x, y;
};

#endif