#ifndef MATRIX4_HPP
#define MATRIX4_HPP

#include <array>
#include "vec4.hpp"

class Matrix4 {
  public:
    Matrix4(); // Default to identity
    Matrix4(const std::array<float, 16>& values);

    static Matrix4 identity();
    static Matrix4 perspective(float fov, float aspect, float near, float far);
    static Matrix4 translate(float x, float y, float z);

    Vec4 transform(const Vec4& vec) const;

    Matrix4 operator*(const Matrix4& other) const;
    Vec4 operator*(const Vec4& vec) const;

    float& operator()(int row, int col);
    const float& operator()(int row, int col) const;

    void setRow(int row, const std::array<float, 4>& values);
    void setColumn(int col, const std::array<float, 4>& values);
    std::array<float, 4> getRow(int row) const;
    std::array<float, 4> getColumn(int col) const;

  private:
    std::array<float, 16> m;
};

inline float& Matrix4::operator()(int row, int col)
{
  return m[row * 4 + col];
}

inline const float& Matrix4::operator()(int row, int col) const
{
  return m[row * 4 + col];
}

inline void Matrix4::setRow(int row, const std::array<float, 4>& values)
{
  for (int col = 0; col < 4; col++)
  {
    (*this)(row, col) = values[col];
  }
}

inline void Matrix4::setColumn(int col, const std::array<float, 4>& values)
{
  for (int row = 0; row < 4; row++)
  {
    (*this)(row, col) = values[row];
  }
}

inline std::array<float, 4> Matrix4::getRow(int row) const
{
  std::array<float, 4> rowData;
  for (int col = 0; col < 4; col++)
  {
    rowData[col] = (*this)(row, col);
  }
  return rowData;
}

inline std::array<float, 4> Matrix4::getColumn(int col) const
{
  std::array<float, 4> colData;
  for (int row = 0; row < 4; row++)
  {
    colData[row] = (*this)(row, col);
  }
  return colData;
}

#endif

