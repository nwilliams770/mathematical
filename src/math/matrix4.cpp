#include "matrix4.hpp"

Matrix4::Matrix4()
{
  m = {1.0f, 0.0f, 0.0f, 0.0f,
       0.0f, 1.0f, 0.0f, 0.0f,
       0.0f, 0.0f, 1.0f, 0.0f,
       0.0f, 0.0f, 0.0f, 1.0f};
}

Matrix4::Matrix4(const std::array<float, 16>& values) : m(values) {}

Vec4 Matrix4::transform(const Vec4& vec) const {
  return Vec4(
    m[0] * vec.x + m[1] * vec.y + m[2] * vec.z + m[3] * vec.w,
    m[4] * vec.x + m[5] * vec.y + m[6] * vec.z + m[7] * vec.w,
    m[8] * vec.x + m[9] * vec.y + m[10] * vec.z + m[11] * vec.w,
    m[12] * vec.x + m[13] * vec.y + m[14] * vec.z + m[15] * vec.w
  );
}

Matrix4 Matrix4::operator*(const Matrix4& other) const {
  Matrix4 result;
  for (int row = 0; row < 4; ++row) {
    for (int col = 0; col < 4; ++col) {
      result.m[row * 4 + col] = 0.0f;
      for (int k = 0; k < 4; ++k) {
        result.m[row * 4 + col] += m[row * 4 + k] * other.m[k * 4 + col];
      }
    }
  }
  return result;
}

Vec4 Matrix4::operator*(const Vec4& vec) const {
  return Vec4(
    m[0] * vec.x + m[4] * vec.y + m[8] * vec.z + m[12] * vec.w,
    m[1] * vec.x + m[5] * vec.y + m[9] * vec.z + m[13] * vec.w,
    m[2] * vec.x + m[6] * vec.y + m[10] * vec.z + m[14] * vec.w,
    m[3] * vec.x + m[7] * vec.y + m[11] * vec.z + m[15] * vec.w
  );
}

// Static methods
Matrix4 Matrix4::translate(float x, float y, float z) {
  return Matrix4({
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    x,    y,    z,    1.0f
  });
}

Matrix4 Matrix4::perspective(float fieldOfViewYRadians, float aspectRatio, float nearClip, float farClip) {
  float zoomY = 1 / std::tan(fieldOfViewYRadians / 2);
  float zoomX = zoomY / aspectRatio;
  return Matrix4({
    zoomX, 0.0f, 0.0f, 0.0f,
    0.0f, zoomY, 0.0f, 0.0f,
    0.0f, 0.0f, ((farClip + nearClip) / (farClip - nearClip)), 1.0f,
    0.0f, 0.0f, ((-2.0f * nearClip * farClip) / (farClip - nearClip)), 0.0f
  });
}
// Static methods
Matrix4 Matrix4::identity()
{
  return Matrix4();
}
