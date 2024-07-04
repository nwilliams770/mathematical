#include <gtest/gtest.h>
#include "camera.hpp"
#include "vec3.hpp"
#include "matrix4.hpp"


// Test initialization
#include <gtest/gtest.h>
#include "view_frustum.hpp"
#include "camera.hpp"
#include "vec3.hpp"
#include "matrix4.hpp"


TEST(ViewFrustumTest, Initialization) {
  float fov = 45.0f * M_PI / 180.0f; // 45 degrees in radians
  float aspectRatio = 16.0f / 9.0f;
  float nearClip = 0.1f;
  float farClip = 100.0f;

  ViewFrustum frustum(fov, aspectRatio, nearClip, farClip);
  Matrix4 projectionMatrix = frustum.getProjectionMatrix();

  EXPECT_FLOAT_EQ(projectionMatrix(0, 0), 1.3579951f);
  EXPECT_FLOAT_EQ(projectionMatrix(1, 1), 2.4142136f);
  EXPECT_FLOAT_EQ(projectionMatrix(2, 2), 1.002002f);
  EXPECT_FLOAT_EQ(projectionMatrix(2, 3), 1.0f);
  EXPECT_FLOAT_EQ(projectionMatrix(3, 2), -0.2002002f);
}


TEST(ViewFrustumTest, IsAABBInside) {
  Camera camera(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 1.0f));
  float fov = 45.0f * M_PI / 180.0f; // 45 degrees in radians
  float aspectRatio = 16.0f / 9.0f;
  float nearClip = 0.1f;
  float farClip = 100.0f;

  ViewFrustum frustum(fov, aspectRatio, nearClip, farClip);
  frustum.update(camera);

  Vec3 minInside(-1.0f, -1.0f, 1.0f);
  Vec3 maxInside(1.0f, 1.0f, 10.0f);
  Vec3 minOutside(-1.0f, -1.0f, 200.0f);
  Vec3 maxOutside(1.0f, 1.0f, 300.0f);

  EXPECT_TRUE(frustum.isAABBInside(minInside, maxInside));
  EXPECT_FALSE(frustum.isAABBInside(minOutside, maxOutside));
}

// Test the projection matrix generation
TEST(ViewFrustumTest, ProjectionMatrix) {
    float fov = 45.0f * M_PI / 180.0f; // 45 degrees in radians
    float aspectRatio = 16.0f / 9.0f;
    float nearClip = 0.1f;
    float farClip = 100.0f;

    ViewFrustum frustum(fov, aspectRatio, nearClip, farClip);
    Matrix4 projectionMatrix = frustum.getProjectionMatrix();

    float zoomY = 1 / std::tan(fov / 2);
    float zoomX = zoomY / aspectRatio;
    EXPECT_FLOAT_EQ(projectionMatrix(0, 0), zoomX);
    EXPECT_FLOAT_EQ(projectionMatrix(1, 1), zoomY);
    EXPECT_FLOAT_EQ(projectionMatrix(2, 2), (farClip + nearClip) / (farClip - nearClip));
    EXPECT_FLOAT_EQ(projectionMatrix(2, 3), 1.0f);
    EXPECT_FLOAT_EQ(projectionMatrix(3, 2), (-2 * nearClip * farClip) / (farClip - nearClip));
    EXPECT_FLOAT_EQ(projectionMatrix(3, 3), 0.0f);
}

TEST(ViewFrustumTest, ViewProjectionMatrixMultiplication) {
    Camera camera(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 1.0f));
    float fov = 45.0f * M_PI / 180.0f;
    float aspectRatio = 16.0f / 9.0f;
    float nearClip = 0.1f;
    float farClip = 100.0f;

    ViewFrustum frustum(fov, aspectRatio, nearClip, farClip);
    Matrix4 projectionMatrix = frustum.getProjectionMatrix();
    Matrix4 viewMatrix = camera.getViewMatrix();
    Matrix4 viewProjectionMatrix = projectionMatrix * viewMatrix;

    // Logging matrix values for comparison
    LOG("ViewProjectionMatrix:");
    for (int row = 0; row < 4; ++row) {
        auto rowData = viewProjectionMatrix.getRow(row);
        LOG_ARGS("Row", row, rowData[0], rowData[1], rowData[2], rowData[3]);
    }

    EXPECT_NEAR(viewProjectionMatrix(0, 0), 1.357995, 1e-5);
    EXPECT_NEAR(viewProjectionMatrix(1, 1), 2.4142136, 1e-5);
    EXPECT_NEAR(viewProjectionMatrix(2, 2), 1.002002, 1e-5);
    EXPECT_NEAR(viewProjectionMatrix(2, 3), 1.0f, 1e-5);
    EXPECT_NEAR(viewProjectionMatrix(3, 2), -0.2002002, 1e-5);
    EXPECT_NEAR(viewProjectionMatrix(3, 3), 0.0f, 1e-5);
}