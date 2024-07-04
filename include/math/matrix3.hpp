#ifndef MATRIX33_HPP
#define MATRIX33_HPP

#include <array>
#include "vec3.hpp"

class Matrix3
{
  public:
    Matrix3(); // Default to identity
    Matrix3(const std::array<float, 9>& values);

    static Matrix3 identity();
    static Matrix3 rotationX(float angle);
    static Matrix3 rotationY(float angle);
    static Matrix3 rotationZ(float angle);
    static Matrix3 scale(float scaleFactor);
    static Matrix3 scale(float scaleX, float scaleY, float scaleZ);

    Vec3 transform(const Vec3& vec) const;

    Matrix3 operator*(const Matrix3& other) const;

    float& operator()(int row, int col);
    const float& operator()(int row, int col) const;

    void setRow(int row, const std::array<float, 3>& values);
    void setColumn(int col, const std::array<float, 3>& values);
    std::array<float, 3> getRow(int row) const;
    std::array<float, 3> getColumn(int col) const;


  private:
    std::array<float, 9> m;
};

inline float& Matrix3::operator()(int row, int col)
{
  return m[row * 3 + col];
};

inline const float& Matrix3::operator()(int row, int col) const
{
  return m[row * 3 + col];
};

inline void Matrix3::setRow(int row, const std::array<float, 3>& values)
{
  for (int col = 0; col < 3; col++)
  {
    (*this)(row, col) = values[col];
  }
};

inline void Matrix3::setColumn(int col, const std::array<float, 3>& values)
{
  for (int row = 0; row < 3; row++)
  {
    (*this)(row, col) = values[row];
  }
};

inline std::array<float, 3> Matrix3::getRow(int row) const
{
  std::array<float, 3> rowData;
  for (int col = 0; col < 3; col++)
  {
    rowData[col] = (*this)(row, col);
  }
  return rowData;
};

inline std::array<float, 3> Matrix3::getColumn(int col) const
{
  std::array<float, 3> colData;
  for (int row = 0; row < 3; row++)
  {
    colData[row] = (*this)(row, col);
  }
  return colData;
};

#endif