#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "vec3.hpp"

class Camera
{
  public:
    Camera(const Vec3& position = Vec3(), const Vec3& direction = Vec3(0, 0, -1), const Vec3& up = Vec3(0, 1, 0), float focalLength);

    // Movements
    // void move(Vec3 direction); TODO if needed
    void moveForward(float distance);
    void moveBackward(float distance);
    void moveLeft(float distance);
    void moveRight(float distance);

    // Rotations
    // void rotate(float heading, float pitch, float bank); TODO if needed
    // Y-axis (Heading)
    void turnLeft(float angle);
    void turnRight(float angle);

    // X-axis (Pitch)
    void lookUp(float angle);
    void lookDown(float angle);

    // Z-axis (Bank)
    void tiltLeft(float angle);
    void tiltRight(float angle);

    // Methods to handle input for walking through the scene
    void handleInput(const char input);  // 'w', 'a', 's', 'd' for movement, 'q', 'e' for rotation, etc.

    Vec3 getPosition() const { return position; }
    Vec3 getDirection() const { return direction; }
    Vec3 getUp() const { return up; }
    float getFocalLength() const { return focalLength; }

  private:
    Vec3 position;
    Vec3 direction;
    Vec3 up;
    float focalLength;
};

#endif