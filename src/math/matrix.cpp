#include "matrix.hpp"

Matrix::Matrix()
{
  m = {1.0f, 0.0f, 0.0f,
       0.0f, 1.0f, 0.0f,
       0.0f, 0.0f, 1.0f};
};

Matrix::Matrix(const std::array<float, 9>& values) : m(values) {};

Vec3 Matrix::transform(const Vec3& vec) const {
  return Vec3(
    m[0] * vec.x + m[1] * vec.y + m[2] * vec.z,
    m[3] * vec.x + m[4] * vec.y + m[5] * vec.z,
    m[6] * vec.x + m[7] * vec.y + m[8] * vec.z
  );
}

Matrix Matrix::operator*(const Matrix& other) const {
  Matrix result;
  for (int row = 0; row < 3; ++row) {
    for (int col = 0; col < 3; ++col) {
      result(row, col) = 0.0f;
      for (int k = 0; k < 3; ++k) {
        result(row, col) += (*this)(row, k) * other(k, col);
      }
    }
  }
  return result;
}

// Static methods
Matrix Matrix::identity()
{
  return Matrix();
};

Matrix Matrix::rotationX(float angle) {
  float c = std::cos(angle);
  float s = std::sin(angle);
  return Matrix({
    1.0f, 0.0f, 0.0f,
    0.0f, c, -s,
    0.0f, s, c
  });
}

Matrix Matrix::rotationY(float angle) {
    float c = std::cos(angle);
    float s = std::sin(angle);
    return Matrix({
      c, 0.0f, s,
      0.0f, 1.0f, 0.0f,
      -s, 0.0f, c
    });
}

Matrix Matrix::rotationZ(float angle) {
  float c = std::cos(angle);
  float s = std::sin(angle);
  return Matrix({
    c, -s, 0.0f,
    s, c, 0.0f,
    0.0f, 0.0f, 1.0f
  });
}

Matrix Matrix::scale(float scaleFactor) {
  return Matrix({
    scaleFactor, 0.0f, 0.0f,
    0.0f, scaleFactor, 0.0f,
    0.0f, 0.0f, scaleFactor
  });
}

Matrix Matrix::scale(float scaleX, float scaleY, float scaleZ) {
  return Matrix({
    scaleX, 0.0f, 0.0f,
    0.0f, scaleY, 0.0f,
    0.0f, 0.0f, scaleZ
  });
}
