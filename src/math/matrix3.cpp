#include "matrix3.hpp"

Matrix3::Matrix3()
{
  m = {1.0f, 0.0f, 0.0f,
       0.0f, 1.0f, 0.0f,
       0.0f, 0.0f, 1.0f};
}

Matrix3::Matrix3(const std::array<float, 9>& values) : m(values) {}

Vec3 Matrix3::transform(const Vec3& vec) const {
  return Vec3(
    m[0] * vec.x + m[1] * vec.y + m[2] * vec.z,
    m[3] * vec.x + m[4] * vec.y + m[5] * vec.z,
    m[6] * vec.x + m[7] * vec.y + m[8] * vec.z
  );
}

Matrix3 Matrix3::operator*(const Matrix3& other) const {
  Matrix3 result;
  for (int row = 0; row < 3; ++row) {
    for (int col = 0; col < 3; ++col) {
      result.m[row * 3 + col] = 0.0f;
      for (int k = 0; k < 3; ++k) {
        result.m[row * 3 + col] += m[row * 3 + k] * other.m[k * 3 + col];
      }
    }
  }
  return result;
}

// Static methods
Matrix3 Matrix3::identity()
{
  return Matrix3();
}

Matrix3 Matrix3::rotationX(float angle) {
  float c = std::cos(angle);
  float s = std::sin(angle);
  return Matrix3({
    1.0f, 0.0f, 0.0f,
    0.0f, c, -s,
    0.0f, s, c
  });
}

Matrix3 Matrix3::rotationY(float angle) {
    float c = std::cos(angle);
    float s = std::sin(angle);
    return Matrix3({
      c, 0.0f, s,
      0.0f, 1.0f, 0.0f,
      -s, 0.0f, c
    });
}

Matrix3 Matrix3::rotationZ(float angle) {
  float c = std::cos(angle);
  float s = std::sin(angle);
  return Matrix3({
    c, -s, 0.0f,
    s, c, 0.0f,
    0.0f, 0.0f, 1.0f
  });
}

Matrix3 Matrix3::scale(float scaleFactor) {
  return Matrix3({
    scaleFactor, 0.0f, 0.0f,
    0.0f, scaleFactor, 0.0f,
    0.0f, 0.0f, scaleFactor
  });
}

Matrix3 Matrix3::scale(float scaleX, float scaleY, float scaleZ) {
  return Matrix3({
    scaleX, 0.0f, 0.0f,
    0.0f, scaleY, 0.0f,
    0.0f, 0.0f, scaleZ
  });
}
