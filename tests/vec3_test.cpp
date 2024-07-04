#include <gtest/gtest.h>
#include "vec3.hpp"

#include <gtest/gtest.h>
#include "vec3.hpp"

// Test default constructor and initialization with values
TEST(Vec3Test, Initialization) {
  Vec3 vec1;
  EXPECT_FLOAT_EQ(vec1.x, 0.0f);
  EXPECT_FLOAT_EQ(vec1.y, 0.0f);
  EXPECT_FLOAT_EQ(vec1.z, 0.0f);

  Vec3 vec2(1.0f, 2.0f, 3.0f);
  EXPECT_FLOAT_EQ(vec2.x, 1.0f);
  EXPECT_FLOAT_EQ(vec2.y, 2.0f);
  EXPECT_FLOAT_EQ(vec2.z, 3.0f);
}

// Test cross product
TEST(Vec3Test, CrossProduct) {
  Vec3 vec1(1.0f, 0.0f, 0.0f);
  Vec3 vec2(0.0f, 1.0f, 0.0f);
  Vec3 result = vec1.cross(vec2);

  EXPECT_FLOAT_EQ(result.x, 0.0f);
  EXPECT_FLOAT_EQ(result.y, 0.0f);
  EXPECT_FLOAT_EQ(result.z, 1.0f);
}

// Test dot product
TEST(Vec3Test, DotProduct) {
  Vec3 vec1(1.0f, 2.0f, 3.0f);
  Vec3 vec2(4.0f, 5.0f, 6.0f);
  float result = vec1.dot(vec2);

  EXPECT_FLOAT_EQ(result, 32.0f);
}

// Test negation operator
TEST(Vec3Test, Negation) {
  Vec3 vec(1.0f, -2.0f, 3.0f);
  Vec3 result = -vec;

  EXPECT_FLOAT_EQ(result.x, -1.0f);
  EXPECT_FLOAT_EQ(result.y, 2.0f);
  EXPECT_FLOAT_EQ(result.z, -3.0f);
}

// Test addition operator
TEST(Vec3Test, Addition) {
  Vec3 vec1(1.0f, 2.0f, 3.0f);
  Vec3 vec2(4.0f, 5.0f, 6.0f);
  Vec3 result = vec1 + vec2;

  EXPECT_FLOAT_EQ(result.x, 5.0f);
  EXPECT_FLOAT_EQ(result.y, 7.0f);
  EXPECT_FLOAT_EQ(result.z, 9.0f);
}

// Test subtraction operator
TEST(Vec3Test, Subtraction) {
  Vec3 vec1(4.0f, 5.0f, 6.0f);
  Vec3 vec2(1.0f, 2.0f, 3.0f);
  Vec3 result = vec1 - vec2;

  EXPECT_FLOAT_EQ(result.x, 3.0f);
  EXPECT_FLOAT_EQ(result.y, 3.0f);
  EXPECT_FLOAT_EQ(result.z, 3.0f);
}

// Test scalar multiplication operator
TEST(Vec3Test, ScalarMultiplication) {
  Vec3 vec(1.0f, 2.0f, 3.0f);
  Vec3 result = vec * 2.0f;

  EXPECT_FLOAT_EQ(result.x, 2.0f);
  EXPECT_FLOAT_EQ(result.y, 4.0f);
  EXPECT_FLOAT_EQ(result.z, 6.0f);
}

// Test scalar division operator
TEST(Vec3Test, ScalarDivision) {
  Vec3 vec(4.0f, 6.0f, 8.0f);
  Vec3 result = vec / 2.0f;

  EXPECT_FLOAT_EQ(result.x, 2.0f);
  EXPECT_FLOAT_EQ(result.y, 3.0f);
  EXPECT_FLOAT_EQ(result.z, 4.0f);
}

// Test scalar division by zero
TEST(Vec3Test, ScalarDivisionByZero) {
  Vec3 vec(4.0f, 6.0f, 8.0f);
  EXPECT_THROW(vec / 0.0f, std::runtime_error);
}

// Test addition assignment operator
TEST(Vec3Test, AdditionAssignment) {
  Vec3 vec1(1.0f, 2.0f, 3.0f);
  Vec3 vec2(4.0f, 5.0f, 6.0f);
  vec1 += vec2;

  EXPECT_FLOAT_EQ(vec1.x, 5.0f);
  EXPECT_FLOAT_EQ(vec1.y, 7.0f);
  EXPECT_FLOAT_EQ(vec1.z, 9.0f);
}

// Test subtraction assignment operator
TEST(Vec3Test, SubtractionAssignment) {
  Vec3 vec1(4.0f, 5.0f, 6.0f);
  Vec3 vec2(1.0f, 2.0f, 3.0f);
  vec1 -= vec2;

  EXPECT_FLOAT_EQ(vec1.x, 3.0f);
  EXPECT_FLOAT_EQ(vec1.y, 3.0f);
  EXPECT_FLOAT_EQ(vec1.z, 3.0f);
}

// Test magnitude calculation
TEST(Vec3Test, Magnitude) {
  Vec3 vec(3.0f, 4.0f, 0.0f);
  float result = vec.magnitude();

  EXPECT_FLOAT_EQ(result, 5.0f);
}

// Test normalization
TEST(Vec3Test, Normalize) {
  Vec3 vec(3.0f, 4.0f, 0.0f);
  vec.normalize();

  EXPECT_NEAR(vec.x, 0.6f, 1e-5);
  EXPECT_NEAR(vec.y, 0.8f, 1e-5);
  EXPECT_NEAR(vec.z, 0.0f, 1e-5);
}

// Test normalized method
TEST(Vec3Test, Normalized) {
  Vec3 vec(3.0f, 4.0f, 0.0f);
  Vec3 result = vec.normalized();

  EXPECT_NEAR(result.x, 0.6f, 1e-5);
  EXPECT_NEAR(result.y, 0.8f, 1e-5);
  EXPECT_NEAR(result.z, 0.0f, 1e-5);
}
