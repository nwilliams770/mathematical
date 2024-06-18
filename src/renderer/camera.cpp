#include "camera.hpp"
#include "matrix.hpp"

Camera::Camera(const Vec3& position , const Vec3& direction, const Vec3& up, float focalLength) :
  position(position), direction(direction), up(up), focalLength(focalLength)
{
  this->direction.normalize();
  this->up.normalize();
}

void Camera::moveForward(float distance) { position += (direction * distance); }

void Camera::moveBackward(float distance) { position -= (direction * distance); }

// Right-hand coordinate system
void Camera::moveLeft(float distance)
{
  Vec3 left = up.cross(direction).normalize();
  position += left * distance;
}

// Right-hand coordinate system
void Camera::moveRight(float distance)
{
  Vec3 right = direction.cross(up).normalize();
  position += right * distance;
}

// Y-axis (Heading)
void Camera::turnLeft(float angle)
{
  direction = Matrix::rotationY(angle).transform(direction).normalize();
}

void Camera::turnRight(float angle)
{
  direction = Matrix::rotationY(-angle).transform(direction).normalize();
}

// X-axis (Pitch)
void Camera::lookUp(float angle)
{
  direction = Matrix::rotationX(-angle).transform(direction).normalize();
}

void Camera::lookDown(float angle)
{
  direction = Matrix::rotationX(angle).transform(direction).normalize();
}

// Z-axis (Bank)
void Camera::tiltLeft(float angle)
{
  direction = Matrix::rotationZ(angle).transform(direction).normalize();

}

void Camera::tiltRight(float angle)
{
  direction = Matrix::rotationZ(-angle).transform(direction).normalize();

}

// WASD movement
// QE turn
// RF look (up/down)
// ZX tilt
void Camera::handleInput(const char input)
{
  float moveDistance = 1.0f; // Define movement step size
  float rotateAngle = 0.1f;  // Define rotation step size in radians

  switch (input)
  {
    // TODO: use consts
    case 'w':
      moveForward(moveDistance);
      break;
    case 's':
      moveBackward(moveDistance);
      break;
    case 'a':
      moveLeft(moveDistance);
      break;
    case 'd':
      moveRight(moveDistance);
      break;
    case 'q':
      turnLeft(rotateAngle);
      break;
    case 'e':
      turnRight(rotateAngle);
      break;
    case 'r':
      lookUp(rotateAngle);
      break;
    case 'f':
      lookDown(rotateAngle);
      break;
    case 'z':
      tiltLeft(rotateAngle);
      break;
    case 'x':
      tiltRight(rotateAngle);
      break;
    default:
      break;
  }
}