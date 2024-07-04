#include <gtest/gtest.h>
#include "matrix4.hpp"
#include "vec4.hpp"

// Test default constructor and initialization with values
TEST(Matrix4Test, Initialization) {
  Matrix4 mat1;
  EXPECT_FLOAT_EQ(mat1(0, 0), 1.0f);
  EXPECT_FLOAT_EQ(mat1(1, 1), 1.0f);
  EXPECT_FLOAT_EQ(mat1(2, 2), 1.0f);
  EXPECT_FLOAT_EQ(mat1(3, 3), 1.0f);
}

// Test identity matrix creation
TEST(Matrix4Test, IdentityMatrix) {
  Matrix4 identityMatrix = Matrix4::identity();
  EXPECT_FLOAT_EQ(identityMatrix(0, 0), 1.0f);
  EXPECT_FLOAT_EQ(identityMatrix(1, 1), 1.0f);
  EXPECT_FLOAT_EQ(identityMatrix(2, 2), 1.0f);
  EXPECT_FLOAT_EQ(identityMatrix(3, 3), 1.0f);
}

// Test matrix multiplication
TEST(Matrix4Test, Multiplication) {
  Matrix4 mat1({
    1, 2, 3, 4,
    5, 6, 7, 8,
    9, 10, 11, 12,
    13, 14, 15, 16
  });
  Matrix4 mat2({
    17, 18, 19, 20,
    21, 22, 23, 24,
    25, 26, 27, 28,
    29, 30, 31, 32
  });
  Matrix4 result = mat1 * mat2;

  EXPECT_FLOAT_EQ(result(0, 0), 250);
  EXPECT_FLOAT_EQ(result(0, 1), 260);
  EXPECT_FLOAT_EQ(result(0, 2), 270);
  EXPECT_FLOAT_EQ(result(0, 3), 280);

  EXPECT_FLOAT_EQ(result(1, 0), 618);
  EXPECT_FLOAT_EQ(result(1, 1), 644);
  EXPECT_FLOAT_EQ(result(1, 2), 670);
  EXPECT_FLOAT_EQ(result(1, 3), 696);

  EXPECT_FLOAT_EQ(result(2, 0), 986);
  EXPECT_FLOAT_EQ(result(2, 1), 1028);
  EXPECT_FLOAT_EQ(result(2, 2), 1070);
  EXPECT_FLOAT_EQ(result(2, 3), 1112);

  EXPECT_FLOAT_EQ(result(3, 0), 1354);
  EXPECT_FLOAT_EQ(result(3, 1), 1412);
  EXPECT_FLOAT_EQ(result(3, 2), 1470);
  EXPECT_FLOAT_EQ(result(3, 3), 1528);
}

// Test vector transformation
TEST(Matrix4Test, VectorTransformation) {
  Matrix4 mat({
    1, 2, 3, 4,
    5, 6, 7, 8,
    9, 10, 11, 12,
    13, 14, 15, 16
  });
  Vec4 vec(1, 2, 3, 1);
  Vec4 result = mat.transform(vec);

  EXPECT_FLOAT_EQ(result.x, 18);
  EXPECT_FLOAT_EQ(result.y, 46);
  EXPECT_FLOAT_EQ(result.z, 74);
  EXPECT_FLOAT_EQ(result.w, 102);
}

// Test translation matrix creation
TEST(Matrix4Test, TranslationMatrix) {
  Matrix4 translationMatrix = Matrix4::translate(1.0f, 2.0f, 3.0f);
  EXPECT_FLOAT_EQ(translationMatrix(0, 0), 1.0f);
  EXPECT_FLOAT_EQ(translationMatrix(1, 1), 1.0f);
  EXPECT_FLOAT_EQ(translationMatrix(2, 2), 1.0f);
  EXPECT_FLOAT_EQ(translationMatrix(3, 3), 1.0f);

  EXPECT_FLOAT_EQ(translationMatrix(3, 0), 1.0f);
  EXPECT_FLOAT_EQ(translationMatrix(3, 1), 2.0f);
  EXPECT_FLOAT_EQ(translationMatrix(3, 2), 3.0f);
}

// Test perspective matrix creation
TEST(Matrix4Test, PerspectiveMatrix) {
  float fov = 90.0f * M_PI / 180.0f;
  float aspect = 1.0f;
  float near = 0.1f;
  float far = 100.0f;
  Matrix4 perspectiveMatrix = Matrix4::perspective(fov, aspect, near, far);

  EXPECT_NEAR(perspectiveMatrix(0, 0), 1.0f, 1e-5);
  EXPECT_NEAR(perspectiveMatrix(1, 1), 1.0f, 1e-5);
  EXPECT_NEAR(perspectiveMatrix(2, 2), 1.002002, 1e-5);
  EXPECT_NEAR(perspectiveMatrix(2, 3), 1.0f, 1e-5);
  EXPECT_NEAR(perspectiveMatrix(3, 2), -0.2002002, 1e-5);
  EXPECT_NEAR(perspectiveMatrix(3, 3), 0.0f, 1e-5);
}
