#include "camera.hpp"
#include "matrix.hpp"

Camera::Camera(const Vec3& position , const Vec3& direction, const Vec3& up) :
  position(position), direction(direction), up(up)
{
  this->direction.normalize();
  this->up.normalize();
}

void Camera::moveForward(float distance) { position += (direction * distance); }

void Camera::moveBackward(float distance) { position -= (direction * distance); }


// In a right-handed coordinate system, the right-hand rule states that if you
// point the index finger of your right hand in the direction of the first
// vector (a) and your middle finger in the direction of the second vector (b),
// your thumb points in the direction of the cross product (a×b).
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