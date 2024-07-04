#include <gtest/gtest.h>
#include "matrix3.hpp"
#include "vec3.hpp"

// Test default constructor and identity matrix
TEST(Matrix3Test, DefaultConstructor) {
  Matrix3 mat;
  EXPECT_FLOAT_EQ(mat(0, 0), 1.0f);
  EXPECT_FLOAT_EQ(mat(0, 1), 0.0f);
  EXPECT_FLOAT_EQ(mat(0, 2), 0.0f);
  EXPECT_FLOAT_EQ(mat(1, 0), 0.0f);
  EXPECT_FLOAT_EQ(mat(1, 1), 1.0f);
  EXPECT_FLOAT_EQ(mat(1, 2), 0.0f);
  EXPECT_FLOAT_EQ(mat(2, 0), 0.0f);
  EXPECT_FLOAT_EQ(mat(2, 1), 0.0f);
  EXPECT_FLOAT_EQ(mat(2, 2), 1.0f);
}

// Test matrix initialization with values
TEST(Matrix3Test, Initialization) {
  Matrix3 mat({
    1.0f, 2.0f, 3.0f,
    4.0f, 5.0f, 6.0f,
    7.0f, 8.0f, 9.0f
  });

  EXPECT_FLOAT_EQ(mat(0, 0), 1.0f);
  EXPECT_FLOAT_EQ(mat(0, 1), 2.0f);
  EXPECT_FLOAT_EQ(mat(0, 2), 3.0f);
  EXPECT_FLOAT_EQ(mat(1, 0), 4.0f);
  EXPECT_FLOAT_EQ(mat(1, 1), 5.0f);
  EXPECT_FLOAT_EQ(mat(1, 2), 6.0f);
  EXPECT_FLOAT_EQ(mat(2, 0), 7.0f);
  EXPECT_FLOAT_EQ(mat(2, 1), 8.0f);
  EXPECT_FLOAT_EQ(mat(2, 2), 9.0f);
}

// Test matrix multiplication
TEST(Matrix3Test, Multiplication) {
  Matrix3 mat1({
      1, 2, 3,
      4, 5, 6,
      7, 8, 9
  });
  Matrix3 mat2({
      9, 8, 7,
      6, 5, 4,
      3, 2, 1
  });
  Matrix3 result = mat1 * mat2;

  EXPECT_FLOAT_EQ(result(0, 0), 30);
  EXPECT_FLOAT_EQ(result(0, 1), 24);
  EXPECT_FLOAT_EQ(result(0, 2), 18);
  EXPECT_FLOAT_EQ(result(1, 0), 84);
  EXPECT_FLOAT_EQ(result(1, 1), 69);
  EXPECT_FLOAT_EQ(result(1, 2), 54);
  EXPECT_FLOAT_EQ(result(2, 0), 138);
  EXPECT_FLOAT_EQ(result(2, 1), 114);
  EXPECT_FLOAT_EQ(result(2, 2), 90);
}

// Test rotation matrices
TEST(Matrix3Test, Rotation) {
  float angle = M_PI / 2; // 90 degrees
  Matrix3 rotX = Matrix3::rotationX(angle);
  Matrix3 rotY = Matrix3::rotationY(angle);
  Matrix3 rotZ = Matrix3::rotationZ(angle);

  // Check some expected values for rotation matrices
  EXPECT_NEAR(rotX(1, 1), 0.0f, 1e-5);
  EXPECT_NEAR(rotX(1, 2), -1.0f, 1e-5);
  EXPECT_NEAR(rotX(2, 1), 1.0f, 1e-5);
  EXPECT_NEAR(rotX(2, 2), 0.0f, 1e-5);

  EXPECT_NEAR(rotY(0, 0), 0.0f, 1e-5);
  EXPECT_NEAR(rotY(0, 2), 1.0f, 1e-5);
  EXPECT_NEAR(rotY(2, 0), -1.0f, 1e-5);
  EXPECT_NEAR(rotY(2, 2), 0.0f, 1e-5);

  EXPECT_NEAR(rotZ(0, 0), 0.0f, 1e-5);
  EXPECT_NEAR(rotZ(0, 1), -1.0f, 1e-5);
  EXPECT_NEAR(rotZ(1, 0), 1.0f, 1e-5);
  EXPECT_NEAR(rotZ(1, 1), 0.0f, 1e-5);
}

// Test scaling matrices
TEST(Matrix3Test, Scale) {
  Matrix3 scale1 = Matrix3::scale(2.0f);
  Matrix3 scale2 = Matrix3::scale(2.0f, 3.0f, 4.0f);

  EXPECT_FLOAT_EQ(scale1(0, 0), 2.0f);
  EXPECT_FLOAT_EQ(scale1(1, 1), 2.0f);
  EXPECT_FLOAT_EQ(scale1(2, 2), 2.0f);

  EXPECT_FLOAT_EQ(scale2(0, 0), 2.0f);
  EXPECT_FLOAT_EQ(scale2(1, 1), 3.0f);
  EXPECT_FLOAT_EQ(scale2(2, 2), 4.0f);
}

// Test vector transformation
TEST(Matrix3Test, Transform) {
  Matrix3 mat({
    1, 2, 3,
    4, 5, 6,
    7, 8, 9
  });
  Vec3 vec(1, 2, 3);
  Vec3 result = mat.transform(vec);

  EXPECT_FLOAT_EQ(result.x, 14);
  EXPECT_FLOAT_EQ(result.y, 32);
  EXPECT_FLOAT_EQ(result.z, 50);
}

// Test row and column getters/setters
TEST(Matrix3Test, GetSetRowColumn) {
  Matrix3 mat;
  std::array<float, 3> row = {1, 2, 3};
  std::array<float, 3> col = {4, 5, 6};

  mat.setRow(0, row);
  mat.setColumn(1, col);

  EXPECT_FLOAT_EQ(mat(0, 0), 1.0f);
  EXPECT_FLOAT_EQ(mat(0, 1), 4.0f);
  EXPECT_FLOAT_EQ(mat(0, 2), 3.0f);
  EXPECT_FLOAT_EQ(mat(1, 1), 5.0f);
  EXPECT_FLOAT_EQ(mat(2, 1), 6.0f);

  std::array<float, 3> rowResult = mat.getRow(0);
  std::array<float, 3> colResult = mat.getColumn(1);

  EXPECT_FLOAT_EQ(rowResult[0], 1.0f);
  EXPECT_FLOAT_EQ(rowResult[1], 4.0f);
  EXPECT_FLOAT_EQ(rowResult[2], 3.0f);

  EXPECT_FLOAT_EQ(colResult[0], 4.0f);
  EXPECT_FLOAT_EQ(colResult[1], 5.0f);
  EXPECT_FLOAT_EQ(colResult[2], 6.0f);
}
