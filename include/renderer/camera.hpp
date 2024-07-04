#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "vec3.hpp"
#include "matrix4.hpp"

class Camera
{
  public:
    Camera(const Vec3& position = Vec3(), const Vec3& direction = Vec3(0, 0, 1), const Vec3& up = Vec3(0, 1, 0));

    void move(const Vec3& offset);
    void rotate(const Vec3& axis, float angleInRadians);

    void moveForward(float distance);
    void moveBackward(float distance);
    void moveLeft(float distance);
    void moveRight(float distance);
    void turnLeft(float angle);
    void turnRight(float angle);
    void lookUp(float angle);
    void lookDown(float angle);
    void tiltLeft(float angle);
    void tiltRight(float angle);

    Matrix4 getViewMatrix() const;
    Vec3 getPosition() const { return position; }
    Vec3 getDirection() const { return direction; }
    Vec3 getUp() const { return up; }

    // TODO: make private again
    Vec3 position;
    Vec3 direction;
    Vec3 up;
  private:
};

#endif