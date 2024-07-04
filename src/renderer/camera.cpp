#include <cmath>

#include "camera.hpp"
#include "matrix3.hpp"
#include "matrix4.hpp"


Camera::Camera(const Vec3& position , const Vec3& direction, const Vec3& up) :
  position(position), direction(direction), up(up)
{
  this->direction = this->direction.normalize();
  this->up = this->up.normalize();
}

// The view matrix transforms world coordinates to camera coordinates,
// effectively placing the camera at the origin of the coordinate system.
// This is also known as the "view transform."
Matrix4 Camera::getViewMatrix() const
{
  Vec3 cameraForward = direction.normalized();
  LOG_ARGS("Camera forward at view matrix getting:", cameraForward.x, cameraForward.y, cameraForward.z);

  Vec3 cameraRight = up.cross(cameraForward).normalize();
  LOG_ARGS("Camera right at view matrix getting:", cameraRight.x, cameraRight.y, cameraRight.z);

  Vec3 cameraUp = cameraForward.cross(cameraRight).normalize();
  LOG_ARGS("Camera up at view matrix getting:", cameraUp.x, cameraUp.y, cameraUp.z);


  Matrix4 rotation = Matrix4({
    cameraRight.x, cameraRight.y, cameraRight.z, 0.0f,
    cameraUp.x, cameraUp.y, cameraUp.z, 0.0f,
    cameraForward.x, cameraForward.y, cameraForward.z, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
  });
  LOG_ARGS("rotation for camera view matrix Row 0:", rotation(0, 0), rotation(0, 1), rotation(0, 2), rotation(0, 3));
  LOG_ARGS("rotation for camera view matrix Row 1:", rotation(1, 0), rotation(1, 1), rotation(1, 2), rotation(1, 3));
  LOG_ARGS("rotation for camera view matrix Row 2:", rotation(2, 0), rotation(2, 1), rotation(2, 2), rotation(2, 3));
  LOG_ARGS("rotation for camera view matrix Row 3:", rotation(3, 0), rotation(3, 1), rotation(3, 2), rotation(3, 3));


  Matrix4 translation = Matrix4::translate(-position.x, -position.y, -position.z);
  LOG_ARGS("translation for camera view matrix Row 0:", translation(0, 0), translation(0, 1), translation(0, 2), translation(0, 3));
  LOG_ARGS("translation for camera view matrix Row 1:", translation(1, 0), translation(1, 1), translation(1, 2), translation(1, 3));
  LOG_ARGS("translation for camera view matrix Row 2:", translation(2, 0), translation(2, 1), translation(2, 2), translation(2, 3));
  LOG_ARGS("translation for camera view matrix Row 3:", translation(3, 0), translation(3, 1), translation(3, 2), translation(3, 3));

  Matrix4 viewMatrix = rotation * translation;
  LOG_ARGS("viewMatrix Row 0:", viewMatrix(0, 0), viewMatrix(0, 1), viewMatrix(0, 2), viewMatrix(0, 3));
  LOG_ARGS("viewMatrix Row 1:", viewMatrix(1, 0), viewMatrix(1, 1), viewMatrix(1, 2), viewMatrix(1, 3));
  LOG_ARGS("viewMatrix Row 2:", viewMatrix(2, 0), viewMatrix(2, 1), viewMatrix(2, 2), viewMatrix(2, 3));
  LOG_ARGS("viewMatrix Row 3:", viewMatrix(3, 0), viewMatrix(3, 1), viewMatrix(3, 2), viewMatrix(3, 3));

  return viewMatrix;
};


void Camera::move(const Vec3& offset)
{
  position += offset;
  LOG_ARGS("Camera moved to position: (", position.x, ",", position.y, ",", position.z, ")");
}

void Camera::rotate(const Vec3& axis, float angleInRadians)
{
  Matrix3 rotation;
  if (axis == Vec3{1, 0, 0})
  {
    rotation = Matrix3::rotationX(angleInRadians);
  } else if (axis == Vec3{0, 1, 0})
  {
    rotation = Matrix3::rotationY(angleInRadians);

  } else if (axis == Vec3{0, 0, 1})
  {
    rotation = Matrix3::rotationZ(angleInRadians);
  }

  direction = rotation.transform(direction).normalize();
  up = rotation.transform(up).normalize();

  LOG_ARGS("Camera rotated. New direction: (", direction.x, ",", direction.y, ",", direction.z, ")", "New direction:" "(", up.x, ",", up.y, ",", up.z, ")");
}

void Camera::moveForward(float distance) { move(direction * distance); }
void Camera::moveBackward(float distance) { move(direction * -distance); }
void Camera::moveLeft(float distance) {
    Vec3 left = direction.cross(up).normalize();
    move(left * distance);
}
void Camera::moveRight(float distance) {
    Vec3 right = up.cross(direction).normalize();
    move(right * distance);
}

// Y-axis (Heading)
void Camera::turnLeft(float angle) { rotate(up, angle); }
void Camera::turnRight(float angle) { rotate(up, -angle); }
// X-axis (Pitch)
void Camera::lookUp(float angle) { rotate(direction.cross(up).normalize(), angle); }
void Camera::lookDown(float angle) { rotate(direction.cross(up).normalize(), -angle); }
// Z-axis (Bank)
void Camera::tiltLeft(float angle) { rotate(direction, angle); }
void Camera::tiltRight(float angle) { rotate(direction, -angle); }