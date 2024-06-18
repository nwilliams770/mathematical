#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <array>
#include "vec3.hpp"

class Matrix
{
  public:
    Matrix(); // Default to identity
    Matrix(const std::array<float, 9>& values);

    static Matrix identity();
    static Matrix rotationX(float angle);
    static Matrix rotationY(float angle);
    static Matrix rotationZ(float angle);
    static Matrix scale(float scaleFactor);
    static Matrix scale(float scaleX, float scaleY, float scaleZ);

    Vec3 transform(const Vec3& vec) const;

    Matrix operator*(const Matrix& other) const;

    float& operator()(int row, int col);
    const float& operator()(int row, int col) const;

    void setRow(int row, const std::array<float, 3>& values);
    void setColumn(int col, const std::array<float, 3>& values);
    std::array<float, 3> getRow(int row) const;
    std::array<float, 3> getColumn(int col) const;


  private:
    std::array<float, 9> m;
};

inline float& Matrix::operator()(int row, int col)
{
  return m[row * 3 + col];
};

inline const float& Matrix::operator()(int row, int col) const
{
  return m[row * 3 + col];
};

inline void Matrix::setRow(int row, const std::array<float, 3>& values)
{
  for (int col = 0; col < 3; col++)
  {
    (*this)(row, col) = values[col];
  }
};

inline void Matrix::setColumn(int col, const std::array<float, 3>& values)
{
  for (int row = 0; row < 3; row++)
  {
    (*this)(row, col) = values[row];
  }
};

inline std::array<float, 3> Matrix::getRow(int row) const
{
  std::array<float, 3> rowData;
  for (int col = 0; col < 3; col++)
  {
    rowData[col] = (*this)(row, col);
  }
  return rowData;
};

inline std::array<float, 3> Matrix::getColumn(int col) const
{
  std::array<float, 3> colData;
  for (int row = 0; row < 3; row++)
  {
    colData[row] = (*this)(row, col);
  }
  return colData;
};

#endif