#include <gtest/gtest.h>
#include "vec4.hpp"
#include "vec3.hpp"

// Test default constructor and initialization with values
TEST(Vec4Test, Initialization) {
  Vec4 vec1;
  EXPECT_FLOAT_EQ(vec1.x, 0.0f);
  EXPECT_FLOAT_EQ(vec1.y, 0.0f);
  EXPECT_FLOAT_EQ(vec1.z, 0.0f);
  EXPECT_FLOAT_EQ(vec1.w, 1.0f);

  Vec4 vec2(1.0f, 2.0f, 3.0f, 4.0f);
  EXPECT_FLOAT_EQ(vec2.x, 1.0f);
  EXPECT_FLOAT_EQ(vec2.y, 2.0f);
  EXPECT_FLOAT_EQ(vec2.z, 3.0f);
  EXPECT_FLOAT_EQ(vec2.w, 4.0f);

  Vec3 vec3(1.0f, 2.0f, 3.0f);
  Vec4 vec4(vec3, 4.0f);
  EXPECT_FLOAT_EQ(vec4.x, 1.0f);
  EXPECT_FLOAT_EQ(vec4.y, 2.0f);
  EXPECT_FLOAT_EQ(vec4.z, 3.0f);
  EXPECT_FLOAT_EQ(vec4.w, 4.0f);
}

// Test vector addition
TEST(Vec4Test, Addition) {
  Vec4 vec1(1.0f, 2.0f, 3.0f, 4.0f);
  Vec4 vec2(5.0f, 6.0f, 7.0f, 8.0f);
  Vec4 result = vec1 + vec2;

  EXPECT_FLOAT_EQ(result.x, 6.0f);
  EXPECT_FLOAT_EQ(result.y, 8.0f);
  EXPECT_FLOAT_EQ(result.z, 10.0f);
  EXPECT_FLOAT_EQ(result.w, 4.0f); // w remains unchanged
}

// Test vector subtraction
TEST(Vec4Test, Subtraction) {
  Vec4 vec1(1.0f, 2.0f, 3.0f, 4.0f);
  Vec4 vec2(5.0f, 6.0f, 7.0f, 8.0f);
  Vec4 result = vec1 - vec2;

  EXPECT_FLOAT_EQ(result.x, -4.0f);
  EXPECT_FLOAT_EQ(result.y, -4.0f);
  EXPECT_FLOAT_EQ(result.z, -4.0f);
  EXPECT_FLOAT_EQ(result.w, 4.0f); // w remains unchanged
}

// Test scalar multiplication
TEST(Vec4Test, ScalarMultiplication) {
  Vec4 vec(1.0f, 2.0f, 3.0f, 4.0f);
  Vec4 result = vec * 2.0f;

  EXPECT_FLOAT_EQ(result.x, 2.0f);
  EXPECT_FLOAT_EQ(result.y, 4.0f);
  EXPECT_FLOAT_EQ(result.z, 6.0f);
  EXPECT_FLOAT_EQ(result.w, 4.0f); // w remains unchanged
}

// Test scalar division
TEST(Vec4Test, ScalarDivision) {
  Vec4 vec(4.0f, 8.0f, 12.0f, 16.0f);
  vec /= 2.0f;

  EXPECT_FLOAT_EQ(vec.x, 2.0f);
  EXPECT_FLOAT_EQ(vec.y, 4.0f);
  EXPECT_FLOAT_EQ(vec.z, 6.0f);
  EXPECT_FLOAT_EQ(vec.w, 8.0f); // w should also be scaled for perspective divide
}

// Test vector magnitude
TEST(Vec4Test, Magnitude) {
  Vec4 vec(1.0f, 2.0f, 3.0f, 4.0f);
  float magnitude = vec.magnitude();

  EXPECT_FLOAT_EQ(magnitude, std::sqrt(1.0f * 1.0f + 2.0f * 2.0f + 3.0f * 3.0f + 4.0f * 4.0f));
}

// Test vector normalization
TEST(Vec4Test, Normalization) {
  Vec4 vec(1.0f, 2.0f, 3.0f, 4.0f);
  Vec4 normalizedVec = vec.normalized();

  float magnitude = vec.magnitude(); // Use the updated magnitude function
  EXPECT_FLOAT_EQ(normalizedVec.x, 1.0f / magnitude);
  EXPECT_FLOAT_EQ(normalizedVec.y, 2.0f / magnitude);
  EXPECT_FLOAT_EQ(normalizedVec.z, 3.0f / magnitude);
  EXPECT_FLOAT_EQ(normalizedVec.w, 4.0f / magnitude);

  // Check in-place normalization
  vec.normalize();
  EXPECT_FLOAT_EQ(vec.x, 1.0f / magnitude);
  EXPECT_FLOAT_EQ(vec.y, 2.0f / magnitude);
  EXPECT_FLOAT_EQ(vec.z, 3.0f / magnitude);
  EXPECT_FLOAT_EQ(vec.w, 4.0f / magnitude);
}
